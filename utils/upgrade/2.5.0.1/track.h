/* Copyright (C) 2005-2025, UNIGINE. All rights reserved.
*
* This file is a part of the UNIGINE 2 SDK.
*
* Your use and / or redistribution of this software in source and / or
* binary form, with or without modification, is subject to: (i) your
* ongoing acceptance of and compliance with the terms and conditions of
* the UNIGINE License Agreement; and (ii) your inclusion of this notice
* in any version of this software that you use or redistribute.
* A copy of the UNIGINE License Agreement is available by contacting
* UNIGINE. at http://unigine.com/
*/

#ifndef __MIGRATION_TRACK_H__
#define __MIGRATION_TRACK_H__

/*
 */
namespace Track {
	
	/*
	 */
	string TRACK_VERSION = "2.5.0.1";
	
	/*
	 */
	void processFile(string file) {
		
		Xml xml = new Xml();
		
		if(!xml.load(file)) {
			Log::error("failed to load \"%s\"",file);
			delete xml;
			return;
		}
		
		string version = xml.getArg("version","1.00");
		if(version >= TRACK_VERSION) {
			delete xml;
			return;
		}
		
		Log::info("upgrading \"%s\"",file);
		
		if(version < "2.0") {
		
			string removed[] = (
				"material.group": 0,
				"material.postDeferred": 0,
				"material.parallaxMask": 0,
				"material.castTranslucent": 0,
				"material.receiveTranslucent": 0,
				"node.light.deferred": 0,
				"node.light.diffuseScale": 0,
				"node.light.specularScale": 0,
				"node.light.specularPower": 0,
				"node.light.translucent": 0,
				"node.light.translucentSize": 0,
				"node.light.shadowAmbient": 0,
				"render.occlusion.ambient.screenRadius": 0,
				"render.occlusion.ambient.sampleRadius": 0,
				"render.occlusion.ambient.perspective": 0,
				"render.occlusion.ambient.attenuation": 0,
				"render.occlusion.ambient.threshold": 0,
				"render.occlusion.ambient.emitter": 0,
				"render.occlusion.ambient.receiver": 0,
				"render.occlusion.ambient.scale": 0,
				"render.occlusion.ambient.power": 0,
				"render.occlusion.light.screenRadius": 0,
				"render.occlusion.light.sampleRadius": 0,
				"render.occlusion.light.perspective": 0,
				"render.occlusion.light.attenuation": 0,
				"render.occlusion.light.threshold": 0,
				"render.occlusion.light.emitter": 0,
				"render.occlusion.light.receiver": 0,
				"render.occlusion.light.scale": 0,
				"render.occlusion.light.power": 0,
				"render.motionBlur.linearScale": 0,
				"render.motionBlur.angularScale": 0,
				"render.hdr.largeExposure": 0,
				"render.hdr.mediumExposure": 0,
				"render.hdr.smallExposure": 0,
			);
			
			string renamed[] = (
				"node.object.particles.swanRate":	"node.object.particles.spawnRate",
				"render.volumetric.exposure":		"render.shadowShafts.exposure",
				"render.volumetric.length":			"render.shadowShafts.length",
				"render.volumetric.attenuation":	"render.shadowShafts.attenuation",
				"render.hdr.lens.texture":			"render.dirtTexture",
				"render.hdr.threshold":				"render.cameraEffects.threshold",
				"render.hdr.exposure":				"render.exposure.scale",
				"render.hdr.adaptation":			"render.exposure.adaptation",
				"render.hdr.minLuminance":			"render.exposure.minLuminance",
				"render.hdr.maxLuminance":			"render.exposure.maxLuminance",
				"render.hdr.brightExposure":		"render.exposure.brightExposure",
				"render.hdr.filmic.shoulderScale":	"render.filmic.shoulderScale",
				"render.hdr.filmic.linearScale":	"render.filmic.linearScale",
				"render.hdr.filmic.linearAngle":	"render.filmic.linearAngle",
				"render.hdr.filmic.toeScale":		"render.filmic.toeScale",
				"render.hdr.filmic.toeNumerator":	"render.filmic.toeNumerator",
				"render.hdr.filmic.toeDenominator":	"render.filmic.toeDenominator",
				"render.hdr.filmic.whiteLevel":		"render.filmic.whiteLevel",
				"render.hdr.cross.enabled":			"render.cross.enabled",
				"render.hdr.cross.color":			"render.cross.color",
				"render.hdr.cross.scale":			"render.cross.scale",
				"render.hdr.cross.shafts":			"render.cross.shafts",
				"render.hdr.cross.length":			"render.cross.length",
				"render.hdr.cross.angle":			"render.cross.angle",
				"render.hdr.cross.threshold":		"render.cross.threshold",
				"render.hdr.bokeh.enabled":			"render.bokeh.enabled",
				"render.hdr.bokeh.color":			"render.bokeh.color",
				"render.hdr.bokeh.scale":			"render.bokeh.scale",
				"render.hdr.bokeh.farSize":			"render.bokeh.farSize",
				"render.hdr.bokeh.farPower":		"render.bokeh.farPower",
				"render.hdr.bokeh.nearSize":		"render.bokeh.nearSize",
				"render.hdr.bokeh.nearPower":		"render.bokeh.nearPower",
				"render.hdr.bokeh.threshold":		"render.bokeh.threshold",
				"render.hdr.bokeh.texture":			"render.bokeh.texture",
				"render.hdr.shaft.enabled":			"render.sunShafts.enabled",
				"render.hdr.shaft.color":			"render.sunShafts.color",
				"render.hdr.shaft.scale":			"render.sunShafts.scale",
				"render.hdr.shaft.length":			"render.sunShafts.length",
				"render.hdr.shaft.attenuation":		"render.sunShafts.attenuation",
				"render.hdr.shaft.threshold":		"render.sunShafts.threshold",
				"render.hdr.lens.enabled":			"render.lens.enabled",
				"render.hdr.lens.color":			"render.lens.color",
				"render.hdr.lens.scale":			"render.lens.scale",
				"render.hdr.lens.length":			"render.lens.length",
				"render.hdr.lens.radius":			"render.lens.radius",
				"render.hdr.lens.threshold":		"render.lens.threshold",
				"render.hdr.lens.dispersion":		"render.lens.dispersion",
			);
			
			for(int i = 0; i < xml.getNumChildren(); i++) {
				
				Xml x = xml.getChild(i);
				
				if(x.getName() != "parameter" || !x.isArg("type")) continue;
				
				if(removed.check(x.getArg("type"))) {
					delete xml.removeChild(x);
					i--;
				} else if(renamed.check(x.getArg("type"))) {
					x.setArg("type",renamed[x.getArg("type")]);
				}
			}
		}
		
		if(version < "2.1") {
		
			string removed[] = (
				"render.ambientColor": 0,
				"render.backgroundColor": 0,
				"render.environment.texture": 0,
				"render.environment.exposure": 0,
				"render.scattering.sunColor": 0,
				"render.scattering.rayColor": 0,
				"render.scattering.mieColor": 0,
				"render.scattering.areal": 0,
				"render.scattering.greenstein": 0,
				"render.scattering.angularity": 0,
				"render.scattering.threshold": 0,
				"render.scattering.energy": 0,
				"render.scattering.power": 0,
				"render.scattering.sun": 0,
				"render.scattering.ray": 0,
				"render.scattering.mie": 0,
				"material.postRefraction": 0,
				"material.postScattering": 0,
			);
			
			for(int i = 0; i < xml.getNumChildren(); i++) {
				
				Xml x = xml.getChild(i);
				
				if(x.getName() != "parameter" || !x.isArg("type")) continue;
				
				if(removed.check(x.getArg("type"))) {
					delete xml.removeChild(x);
					i--;
				}
			}
		}
		
		if(version < "2.2") {
			
			string removed[] = (
				"node.light.world.shadowDistribute": 0,
			);
			
			string renamed[] = (
				"node.light.shadowSize":				"node.light.shadowResolution",
				"node.light.multiplier":				"node.light.intensity",
				"node.light.attenuation":				"node.light.attenuationPower",
				"node.light.environmentprobe.radius":	"node.light.environmentprobe.attenuationDistance",
				"node.light.omni.radius":				"node.light.omni.attenuationDistance",
				"node.light.proj.radius":				"node.light.proj.attenuationDistance",
			);
			
			for(int i = 0; i < xml.getNumChildren(); i++) {
				
				Xml x = xml.getChild(i);
				
				if(x.getName() != "parameter" || !x.isArg("type")) continue;
				
				if(removed.check(x.getArg("type"))) {
					delete xml.removeChild(x);
					i--;
				} else if(renamed.check(x.getArg("type"))) {
					x.setArg("type",renamed[x.getArg("type")]);
				}
			}
		}
		
		if(version < "2.3") {
			
			string removed[] = (
				"render.dof.farBlurRange": 0,
				"render.dof.farBlurRadius": 0,
				"render.dof.farBlurPower": 0,
				"render.dof.farFocalRange": 0,
				"render.dof.farFocalScale": 0,
				"render.dof.farFocalPower": 0,
				"render.dof.nearBlurRange": 0,
				"render.dof.nearBlurRadius": 0,
				"render.dof.nearBlurPower": 0,
				"render.dof.nearFocalRange": 0,
				"render.dof.nearFocalScale": 0,
				"render.dof.nearFocalPower": 0,
				"render.exposure.bright": 0,
				"render.bokeh.enabled": 0,
				"render.bokeh.color": 0,
				"render.bokeh.scale": 0,
				"render.bokeh.farSize": 0,
				"render.bokeh.farPower": 0,
				"render.bokeh.nearSize": 0,
				"render.bokeh.nearPower": 0,
				"render.bokeh.threshold": 0,
				"render.bokeh.texture": 0,
			);
			
			for(int i = 0; i < xml.getNumChildren(); i++) {
				
				Xml x = xml.getChild(i);
				
				if(x.getName() != "parameter" || !x.isArg("type")) continue;
				
				if(removed.check(x.getArg("type"))) {
					delete xml.removeChild(x);
					i--;
				}
			}
		}
		
		xml.setArg("version",TRACK_VERSION);
		
		xml.save(file);
		delete xml;
	}
	
} /* namespace Track */

#endif /* __MIGRATION_TRACK_H__ */
