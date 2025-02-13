/* Copyright (C) 2005-2024, UNIGINE. All rights reserved.
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
// DO NOT EDIT DIRECTLY. This is an auto-generated file. Your changes will be lost.

#pragma once

#include <UnigineMathLib.h>
#include <UnigineObjects.h>

#include "UnigineEditorGlobal.h"
#include "UnigineCollection.h"

namespace UnigineEditor
{


/// <summary> This class is used to manage import parameters for Landscape Layer Map assets(.lmap).</summary>
class UNIGINE_EDITOR_API LandscapeMapImportParameters : public Unigine::APIInterface
{
public:

	/// <summary> Data filling mode. Defines the origin of terrain data. </summary>
	enum DATA_FILLING_MODE
	{
		/// <summary> Manual mode of terrain data. This option is suitable for sculpting the terrain using brushes.</summary>
		DATA_FILLING_MODE_MANUAL = 0,
		/// <summary> Terrain data is stored in a tileset. This type is used to add any available data sources.</summary>
		DATA_FILLING_MODE_FROM_TILESET,
	};

	/// <summary> Type of terrain data sources. </summary>
	enum DATA_SOURCES_TYPE
	{
		/// <summary> Terrain data is taken from available asset files in the 'data' folder. This option is good for small terrains. </summary>
		DATA_SOURCES_TYPE_ASSETS = 0,
		/// <summary> Terrain data is taken from files outside the 'data' folder (e.g., a network disk). An absolute path to the file is specified. This is a recommended option in case of creating a huge terrain using high-density graphic data. </summary>
		DATA_SOURCES_TYPE_EXTERNAL_FILES,
	};

	/// <summary> Type of resolution setting for the Landscape Layer Map. </summary>
	enum RESOLUTION_TYPE
	{
		/// <summary> Resolution is set by the user. Graphic data from textures is remapped to fit the resolution. </summary>
		RESOLUTION_TYPE_AUTO = 0,
		/// <summary> Resolution is automatically detected from the specified textures, the resolution of the biggest texture is used. If a tileset is specified the resulting resolution of all tiles combined will be considered. </summary>
		RESOLUTION_TYPE_MANUAL,
	};

	/// <summary> Pattern matching mode to be used to determine naming in the tileset. Each tile is represented by a single raster image file. The name of such file should contain info on row-column numbers or index of the tile according to a certain pattern, otherwise, the file is ignored.</summary>
	enum PATTERN_MATCHING_MODE
	{
		/// <summary> Row-column numbers or indices are determined automatically according to default patterns: <b>_%X_%Y</b> (for <em>Row-Column</em> mode) or <b>_%X</b> (for <em>Indexed</em> mode).</summary>
		PATTERN_MATCHING_MODE_AUTO = 0,
		/// <summary> A custom naming pattern is specified manually by the user.</summary>
		PATTERN_MATCHING_MODE_MANUAL,
	};

	/// <summary> Naming mode defining the source tileset layout type.</summary>
	enum NAMING_MODE
	{
		/// <summary> Each tile of the source tileset is determined by the row and column numbers. </summary>
		NAMING_MODE_ROW_COLUMN = 0,
		/// <summary> Each tile of the source tileset is determined by an index.</summary>
		NAMING_MODE_INDEXED,
	};

	/// <summary> Order in which the tiles are taken.</summary>
	enum ORDER
	{
		/// <summary> Tiles are taken in direct order from 1 to n (or X:row-Y:column).</summary>
		ORDER_DIRECT = 0,
		/// <summary> Tiles are taken in reversed order from n to 1 (or X:column-Y:row, i.e. rows and columns are swapped).</summary>
		ORDER_INVERSE,
	};

	/// <summary> Data compression type.</summary>
	enum COMPRESSION_TYPE
	{
		/// <summary> Compression is disabled (maximum file size).</summary>
		COMPRESSION_TYPE_OFF = 0,
		/// <summary> Lossless compression Jackalless method is used for the Landscape Layer Map (all data layers).</summary>
		COMPRESSION_TYPE_LOSSLESS,
		/// <summary> Lossless compression Jackalless method is used for the Landscape Layer Map with lossy compression enabled for Albedo, Height Opacity, and Masks data.</summary>
		COMPRESSION_TYPE_LOSSY,
		/// <summary> Custom compression profile enabling selection of compression method for the Landscape Layer Map and options to enable lossy compression for Albedo, Height Opacity, and Masks data separately.</summary>
		COMPRESSION_TYPE_CUSTOM,
	};

	/// <summary> Data compression method.</summary>
	enum COMPRESSION_METHOD
	{
		/// <summary> Jackalless compression method - a lossless compression method providing better compression results for 2D and 3D textures than LZ4 and Zlib without quality reduction (<b><em>Recommended</em></b>)</summary>
		COMPRESSION_METHOD_JACKALLESS = Unigine::Landscape::COMPRESSOR_TYPE_JACKALLESS,
		/// <summary> LZ4 compression method - temporary option, planned to be removed in the upcoming releases.</summary>
		COMPRESSION_METHOD_LZ4 = Unigine::Landscape::COMPRESSOR_TYPE_LZ4,
		/// <summary> Zlib compression method - for high compression ratio (can provide up to 2 times higher compression ratio, but takes up to 20 times longer).</summary>
		COMPRESSION_METHOD_ZLIB = Unigine::Landscape::COMPRESSOR_TYPE_ZLIB,
	};

	/// <summary> Data type to be used for a component of Landscape Layer Map data (heights, albedo, masks).</summary>
	enum DATA_TYPE
	{
		/// <summary> Data is not used at all.</summary>
		DATA_TYPE_NONE = 0,
		/// <summary> Use the data as is. In this case, data of this layer will always overlap data of underlying layers.</summary>
		DATA_TYPE_ONLY_DATA,
		/// <summary> Use the data with an additional opacity mask applied. The mode is useful for data blending with underlying layers.</summary>
		DATA_TYPE_DATA_WITH_OPACITY,
	};

	/// <summary> Blending mode to be used for Landscape Layer Map data components.</summary>
	enum BLENDING_MODE
	{
		/// <summary> Alpha blending mode.</summary>
		BLENDING_MODE_ALPHA_BLEND = Unigine::Landscape::ALPHA_BLEND,
		/// <summary> Additive blending mode.</summary>
		BLENDING_MODE_ADDITIVE = Unigine::Landscape::ADDITIVE,
		/// <summary> Overlay blending mode.</summary>
		BLENDING_MODE_OVERLAY = Unigine::Landscape::OVERLAY,
		/// <summary> Multiplicative blending mode.</summary>
		BLENDING_MODE_MULTIPLICATIVE = Unigine::Landscape::MULTIPLICATIVE,
	};

	/// <summary> Type of heightmap values.</summary>
	enum HEIGHTMAP_VALUES_TYPE
	{
		/// <summary> Heightmap values are normalized.</summary>
		HEIGHTMAP_VALUES_TYPE_NORMALIZED = 0,
		/// <summary> Heightmap values are not normalized.</summary>
		HEIGHTMAP_VALUES_TYPE_UNNORMALIZED,
	};

	/// <summary> Image color channel.</summary>
	enum CHANNEL
	{
		/// <summary> Red channel.</summary>
		CHANNEL_R = 0,
		/// <summary> Green channel.</summary>
		CHANNEL_G,
		/// <summary> Blue channel.</summary>
		CHANNEL_B,
		/// <summary> Alpha channel.</summary>
		CHANNEL_A,
	};

	enum
	{
		/// <summary> Total number of detail masks of the Landscape Terrain.</summary>
		NUM_MASKS = 20,
	};
	/// <summary> Creates a new set of Landscape Map import parameters with default settings.</summary>
	static Unigine::Ptr<LandscapeMapImportParameters> create();
	/// <summary> Loads a set of Landscape Map import parameters from the specified Collection of values.</summary>
	/// <param name='parameters'>Collection containing a set of Landscape Map import parameters to be loaded.</param>
	void load(const Unigine::Ptr<Collection> &parameters);
	/// <summary> Saves a set of Landscape Map import parameters as a new Collection of values.</summary>
	/// <returns> Pointer to a Collection containing the set of Landscape Map import parameters.</returns>
	Unigine::Ptr<Collection> save() const;
	/// <summary> Sets a value indicating if the Landscape Layer Map asset (.lmap) should be regenerated by the Editor.</summary>
	/// <param name='generate'> <b>true</b> - to tell the Editor to regenerate the Landscape Layer Map asset (.lmap), <b>false</b> - to prevent asset regeneration.</param>
	void setForceGenerate(bool generate);
	/// <summary> Returns a value indicating if the Landscape Layer Map asset (.lmap) should be regenerated by the Editor.</summary>
	bool isForceGenerate() const;
	/// <summary> Sets the data filling mode that defines the origin of terrain data. </summary>
	/// <param name='mode'>Data filling mode to be set (see <see cref='DATA_FILLING_MODE'/>).</param>
	void setDataFillingMode(LandscapeMapImportParameters::DATA_FILLING_MODE mode);
	/// <summary> Returns the data filling mode that defines the origin of terrain data. </summary>
	LandscapeMapImportParameters::DATA_FILLING_MODE getDataFillingMode() const;
	/// <summary> Sets the type of terrain data sources. </summary>
	/// <param name='type'>Type of terrain data sources to be set (see <see cref='DATA_SOURCES_TYPE'/>).</param>
	void setDataSourcesType(LandscapeMapImportParameters::DATA_SOURCES_TYPE type);
	/// <summary> Returns the type of terrain data sources. </summary>
	LandscapeMapImportParameters::DATA_SOURCES_TYPE getDataSourcesType() const;
	/// <summary> Sets the type of resolution setting for the Landscape Layer Map. </summary>
	/// <param name='type'>Type of resolution setting to be set (see <see cref='RESOLUTION_TYPE'/>).</param>
	void setResolutionType(LandscapeMapImportParameters::RESOLUTION_TYPE type);
	/// <summary> Returns the type of resolution setting for the Landscape Layer Map. </summary>
	LandscapeMapImportParameters::RESOLUTION_TYPE getResolutionType() const;
	/// <summary> Sets a new resolution for the Landscape Layer Map. </summary>
	/// <param name='resolution'>New resolution for the Landscape Layer Map along the X and Y axes (as a two-component vector).</param>
	void setResolution(const Unigine::Math::ivec2 &resolution);
	/// <summary> Returns a new resolution for the Landscape Layer Map. </summary>
	Unigine::Math::ivec2 getResolution() const;
	/// <summary> Sets a new pattern matching mode to be used to determine naming in the tileset. Each tile is represented by a single raster image file. The name of such file should contain info on row-column numbers or index of the tile according to a certain pattern, otherwise, the file is ignored. </summary>
	/// <param name='mode'>New pattern matching mode to be set (see <see cref='PATTERN_MATCHING_MODE'/>).</param>
	void setPatternMatchingMode(LandscapeMapImportParameters::PATTERN_MATCHING_MODE mode);
	/// <summary> Returns a new pattern matching mode to be used to determine naming in the tileset. Each tile is represented by a single raster image file. The name of such file should contain info on row-column numbers or index of the tile according to a certain pattern, otherwise, the file is ignored. </summary>
	LandscapeMapImportParameters::PATTERN_MATCHING_MODE getPatternMatchingMode() const;
	/// <summary> Sets a value indicating if flipping of tiles along the Y axis is enabled. </summary>
	/// <param name='flipy'> <b>true</b> - to flip tiles along the Y axis, <b>false</b> - to disable flipping.</param>
	void setFlipY(bool flipy);
	/// <summary> Returns a value indicating if flipping of tiles along the Y axis is enabled. </summary>
	bool isFlipY() const;
	/// <summary> Sets a new naming mode defining the source tileset layout type. </summary>
	/// <param name='mode'>New naming mode to be set (see <see cref='NAMING_MODE'/>).</param>
	void setNamingMode(LandscapeMapImportParameters::NAMING_MODE mode);
	/// <summary> Returns a new naming mode defining the source tileset layout type. </summary>
	LandscapeMapImportParameters::NAMING_MODE getNamingMode() const;
	/// <summary> Sets a new horizontal order for the tiles of the source tileset (direct: from 1 to n; or inverse: from n to 1 ). </summary>
	/// <param name='order'>New horizontal order for tiles to be set (see <see cref='ORDER'/>).</param>
	void setHorizontalOrder(LandscapeMapImportParameters::ORDER order);
	/// <summary> Returns a new horizontal order for the tiles of the source tileset (direct: from 1 to n; or inverse: from n to 1 ). </summary>
	LandscapeMapImportParameters::ORDER getHorizontalOrder() const;
	/// <summary> Sets a new vertical order for the tiles of the source tileset (direct: from 1 to n; or inverse: from n to 1 ). </summary>
	/// <param name='order'>New vertical order for tiles to be set (see <see cref='ORDER'/>).</param>
	void setVerticalOrder(LandscapeMapImportParameters::ORDER order);
	/// <summary> Returns a new vertical order for the tiles of the source tileset (direct: from 1 to n; or inverse: from n to 1 ). </summary>
	LandscapeMapImportParameters::ORDER getVerticalOrder() const;
	/// <summary> Sets an order for rows and columns of the source tileset (direct: row-column; or inverse: column-row, when columns and rows are swapped). </summary>
	/// <param name='direction'>New order for rows and columns of the source tileset (see <see cref='ORDER'/>).</param>
	void setOrderDirection(LandscapeMapImportParameters::ORDER direction);
	/// <summary> Returns an order for rows and columns of the source tileset (direct: row-column; or inverse: column-row, when columns and rows are swapped). </summary>
	LandscapeMapImportParameters::ORDER getOrderDirection() const;
	/// <summary> Sets the number of columns of the source tileset. </summary>
	/// <param name='columns'>Number of columns to be set.</param>
	void setNumColumns(int columns);
	/// <summary> Returns the number of columns of the source tileset. </summary>
	int getNumColumns() const;
	/// <summary> Sets a custom user-defined pattern to be used to select data from the tileset. This method is to be used when Pattern Matching Mode is set to <b>Manual</b> (see <see cref='setPatternMatchingMode'/>). </summary>
	/// <param name='pattern'>New custom pattern to be used to select data from the tileset.</param>
	void setPattern(const char *pattern);
	/// <summary> Returns a custom user-defined pattern to be used to select data from the tileset. This method is to be used when Pattern Matching Mode is set to <b>Manual</b> (see <see cref='setPatternMatchingMode'/>). </summary>
	const char *getPattern() const;
	/// <summary> Sets a new compression type for the data layers of the Landscape Layer Map. </summary>
	/// <param name='type'>New compression type to be set (see <see cref='COMPRESSION_TYPE'/>).</param>
	void setCompressionType(LandscapeMapImportParameters::COMPRESSION_TYPE type);
	/// <summary> Returns a new compression type for the data layers of the Landscape Layer Map. </summary>
	LandscapeMapImportParameters::COMPRESSION_TYPE getCompressionType() const;
	/// <summary> Sets a new compression method for the data layers of the Landscape Layer Map. </summary>
	/// <param name='method'>New compression method to be set (see <see cref='COMPRESSION_METHOD'/>).</param>
	void setCompressionMethod(LandscapeMapImportParameters::COMPRESSION_METHOD method);
	/// <summary> Returns a new compression method for the data layers of the Landscape Layer Map. </summary>
	LandscapeMapImportParameters::COMPRESSION_METHOD getCompressionMethod() const;
	/// <summary> Sets the type of data for the Heightmap component of the Landscape Layer Map. Defines how the data for the component is loaded and used.</summary>
	/// <param name='type'>New data type to be set for the Heightmap component (see <see cref='DATA_TYPE'/>).</param>
	void setHeightmapDataType(LandscapeMapImportParameters::DATA_TYPE type);
	/// <summary> Returns the type of data for the Heightmap component of the Landscape Layer Map. Defines how the data for the component is loaded and used.</summary>
	LandscapeMapImportParameters::DATA_TYPE getHeightmapDataType() const;
	/// <summary> Sets a new blending mode to be used for the Heightmap component of the Landscape Layer Map. Defines how the data of this layer is blended with underlying ones. </summary>
	/// <param name='mode'>New blending mode to be set for the Heightmap component (see <see cref='BLENDING_MODE'/>).</param>
	void setHeightmapBlendingMode(LandscapeMapImportParameters::BLENDING_MODE mode);
	/// <summary> Returns a new blending mode to be used for the Heightmap component of the Landscape Layer Map. Defines how the data of this layer is blended with underlying ones. </summary>
	LandscapeMapImportParameters::BLENDING_MODE getHeightmapBlendingMode() const;
	/// <summary> Sets the type of values of the Heightmap component of the Landscape Layer Map. Defines how the data taken from the source is interpreted. </summary>
	/// <param name='type'>New type to be set for the Heightmap values (see <see cref='HEIGHTMAP_VALUES_TYPE'/>).</param>
	void setHeightmapValuesType(LandscapeMapImportParameters::HEIGHTMAP_VALUES_TYPE type);
	/// <summary> Returns the type of values of the Heightmap component of the Landscape Layer Map. Defines how the data taken from the source is interpreted. </summary>
	LandscapeMapImportParameters::HEIGHTMAP_VALUES_TYPE getHeightmapValuesType() const;
	/// <summary> Sets a path to a single-channel source image containing the Heightmap data for the Landscape Layer Map.</summary>
	/// <param name='path'>Path to a single-channel image to be used.</param>
	void setHeightmapPath(const char *path);
	/// <summary> Returns a path to a single-channel source image containing the Heightmap data for the Landscape Layer Map.</summary>
	const char *getHeightmapPath() const;
	/// <summary> Sets a path to a source image containing the Heightmap opacity data for the Landscape Layer Map (1 channel). You can also specify an image channel to be used via the setHeightmapOpacityChannel(). Opacity data is used for blending data between the layers.</summary>
	/// <param name='path'> Path to Heightmap opacity map (1-channel). </param>
	void setHeightmapOpacityPath(const char *path);
	/// <summary> Returns a path to a source image containing the Heightmap opacity data for the Landscape Layer Map (1 channel). You can also specify an image channel to be used via the setHeightmapOpacityChannel(). Opacity data is used for blending data between the layers.</summary>
	const char *getHeightmapOpacityPath() const;
	/// <summary> Sets the channel of the image from which the Heightmap opacity data for the Landscape Layer Map is to be taken. Opacity data is used for blending data between the layers.</summary>
	/// <param name='channel'> Image channel to be used (see <see cref='CHANNEL'/>). </param>
	void setHeightmapOpacityChannel(LandscapeMapImportParameters::CHANNEL channel);
	/// <summary> Returns the channel of the image from which the Heightmap opacity data for the Landscape Layer Map is to be taken. Opacity data is used for blending data between the layers.</summary>
	LandscapeMapImportParameters::CHANNEL getHeightmapOpacityChannel() const;
	/// <summary> Sets the lower limit (min) of the range of normalized Heightmap values of the Landscape Layer Map. This parameter is used when the type of Heightmap values is set to HEIGHTMAP_VALUES_TYPE_NORMALIZED (see <see cref='setHeightmapValuesType'/>).</summary>
	/// <param name='limit'> New lower limit (min) of the normalization range to be set. </param>
	void setHeightmapNormalizationLowerLimit(int limit);
	/// <summary> Returns the lower limit (min) of the range of normalized Heightmap values of the Landscape Layer Map. This parameter is used when the type of Heightmap values is set to HEIGHTMAP_VALUES_TYPE_NORMALIZED (see <see cref='setHeightmapValuesType'/>).</summary>
	int getHeightmapNormalizationLowerLimit() const;
	/// <summary> Sets the upper limit (max) of the range of normalized Heightmap values of the Landscape Layer Map. This parameter is used when the type of Heightmap values is set to HEIGHTMAP_VALUES_TYPE_NORMALIZED (see <see cref='setHeightmapValuesType'/>).</summary>
	/// <param name='limit'> New upper limit (max) of the normalization range to be set. </param>
	void setHeightmapNormalizationUpperLimit(int limit);
	/// <summary> Returns the upper limit (max) of the range of normalized Heightmap values of the Landscape Layer Map. This parameter is used when the type of Heightmap values is set to HEIGHTMAP_VALUES_TYPE_NORMALIZED (see <see cref='setHeightmapValuesType'/>).</summary>
	int getHeightmapNormalizationUpperLimit() const;
	/// <summary> Sets a new fade attenuation to be used for the Heightmap data of the Landscape Layer Map. This parameter defines the distance of the transparency attenuation, starting from the edge of the map. </summary>
	/// <param name='attenuation'>Two-component vector (X, Y) defining fade attenuation of the Heightmap data along X and Y axes.</param>
	void setHeightmapFadeAttenuation(const Unigine::Math::vec2 &attenuation);
	/// <summary> Returns a new fade attenuation to be used for the Heightmap data of the Landscape Layer Map. This parameter defines the distance of the transparency attenuation, starting from the edge of the map. </summary>
	Unigine::Math::vec2 getHeightmapFadeAttenuation() const;
	/// <summary> Sets a value indicating if lossy compression for the Heightmap Opacity data of the Landscape Layer Map is enabled. </summary>
	/// <param name='compression'> <b>true</b> - to enabled lossy compression for the Heightmap Opacity data, <b>false</b> - to use lossless compression (Jackalless method).</param>
	void setHeightmapOpacityLossyCompression(bool compression);
	/// <summary> Returns a value indicating if lossy compression for the Heightmap Opacity data of the Landscape Layer Map is enabled. </summary>
	bool isHeightmapOpacityLossyCompression() const;
	/// <summary> Sets a value indicating if lossy compression for the Albedo component of the Landscape Layer Map is enabled. </summary>
	/// <param name='compression'> <b>true</b> - to enable lossy compression for the Albedo data, <b>false</b> - to use lossless compression (Jackalless method).</param>
	void setAlbedoLossyCompression(bool compression);
	/// <summary> Returns a value indicating if lossy compression for the Albedo component of the Landscape Layer Map is enabled. </summary>
	bool isAlbedoLossyCompression() const;
	/// <summary> Sets a new blending mode to be used for the Albedo component of the Landscape Layer Map. Defines how the data of this layer is blended with underlying ones. </summary>
	/// <param name='mode'>New blending mode to be set for the Albedo component (see <see cref='BLENDING_MODE'/>).</param>
	void setAlbedoBlendingMode(LandscapeMapImportParameters::BLENDING_MODE mode);
	/// <summary> Returns a new blending mode to be used for the Albedo component of the Landscape Layer Map. Defines how the data of this layer is blended with underlying ones. </summary>
	LandscapeMapImportParameters::BLENDING_MODE getAlbedoBlendingMode() const;
	/// <summary> Sets the type of data for the Albedo component of the Landscape Layer Map. Defines how the data for the component is loaded and used.</summary>
	/// <param name='type'>New data type to be set for the Albedo component (see <see cref='DATA_TYPE'/>).</param>
	void setAlbedoDataType(LandscapeMapImportParameters::DATA_TYPE type);
	/// <summary> Returns the type of data for the Albedo component of the Landscape Layer Map. Defines how the data for the component is loaded and used.</summary>
	LandscapeMapImportParameters::DATA_TYPE getAlbedoDataType() const;
	/// <summary> Sets a path to a source image containing the Albedo data for the Landscape Layer Map.</summary>
	/// <param name='path'>Path to albedo color image to be used.</param>
	void setAlbedoPath(const char *path);
	/// <summary> Returns a path to a source image containing the Albedo data for the Landscape Layer Map.</summary>
	const char *getAlbedoPath() const;
	/// <summary> Sets a path to a source image containing the Albedo opacity data for the Landscape Layer Map (1 channel). Opacity data is used for blending data between the layers.</summary>
	/// <param name='path'> Path to albedo opacity map (1-channel). </param>
	void setAlbedoOpacityPath(const char *path);
	/// <summary> Returns a path to a source image containing the Albedo opacity data for the Landscape Layer Map (1 channel). Opacity data is used for blending data between the layers.</summary>
	const char *getAlbedoOpacityPath() const;
	/// <summary> Sets a new fade attenuation to be used for the Albedo data of the Landscape Layer Map. This parameter defines the distance of the transparency attenuation, starting from the edge of the map. </summary>
	/// <param name='attenuation'>Two-component vector (X, Y) defining fade attenuation of the Albedo data along X and Y axes.</param>
	void setAlbedoFadeAttenuation(const Unigine::Math::vec2 &attenuation);
	/// <summary> Returns a new fade attenuation to be used for the Albedo data of the Landscape Layer Map. This parameter defines the distance of the transparency attenuation, starting from the edge of the map. </summary>
	Unigine::Math::vec2 getAlbedoFadeAttenuation() const;
	/// <summary> Sets the channel of the image from which the Albedo opacity data for the Landscape Layer Map is to be taken. Opacity data is used for blending data between the layers.</summary>
	/// <param name='channel'> Image channel to be used (see <see cref='CHANNEL'/>). </param>
	void setAlbedoOpacityChannel(LandscapeMapImportParameters::CHANNEL channel);
	/// <summary> Returns the channel of the image from which the Albedo opacity data for the Landscape Layer Map is to be taken. Opacity data is used for blending data between the layers.</summary>
	LandscapeMapImportParameters::CHANNEL getAlbedoOpacityChannel() const;
	/// <summary> Sets a value indicating if lossy compression for the Masks data of the Landscape Layer Map is enabled. </summary>
	/// <param name='compression'> <b>true</b> - to enable lossy compression for the Masks data, <b>false</b> - to use lossless compression (Jackalless method).</param>
	void setMasksLossyCompression(bool compression);
	/// <summary> Returns a value indicating if lossy compression for the Masks data of the Landscape Layer Map is enabled. </summary>
	bool isMasksLossyCompression() const;
	/// <summary> Sets the type of data for the Masks component of the Landscape Layer Map. Defines how the data for the component is loaded and used.</summary>
	/// <param name='mask_index'> Index of the target detail mask.</param>
	/// <param name='type'> New data type to be set for the Masks component (see <see cref='DATA_TYPE'/>).</param>
	void setMaskDataType(int mask_index, LandscapeMapImportParameters::DATA_TYPE type);
	/// <summary> Returns the current type of data for the Masks component of the Landscape Layer Map. Defines how the data for the component is loaded and used.</summary>
	/// <returns> Current data type for the Masks component (see <see cref='DATA_TYPE'/>).</returns>
	LandscapeMapImportParameters::DATA_TYPE getMaskDataType(int mask_index) const;
	/// <summary> Sets a new name for the detail mask with the specified index. Mask names are synchronized with the current active <a href='https://developer.unigine.com/en/docs/latest/api/library/objects/landscape_terrain/class.objectlandscapeterrain'>ObjectLandscapeTerrain</a>.</summary>
	/// <param name='mask_index'> Index of the target detail mask.</param>
	/// <param name='name'> New name to be set for the detail mask with the specified index.</param>
	void setMaskName(int mask_index, const char *name);
	/// <summary> Returns the current name of the detail mask with the specified index. Mask names are synchronized with the current active <a href='https://developer.unigine.com/en/docs/latest/api/library/objects/landscape_terrain/class.objectlandscapeterrain'>ObjectLandscapeTerrain</a>.</summary>
	/// <param name='mask_index'> Index of the target detail mask.</param>
	/// <returns> Current name of the detail mask with the specified index.</returns>
	const char *getMaskName(int mask_index) const;
	/// <summary> Sets a path to a source image containing the color data for the detail mask with the specified index. You can also specify an image channel to be used via the setMaskColorChannel(). </summary>
	/// <param name='mask_index'> Index of the target detail mask.</param>
	/// <param name='path'> Path to a color image containing the data for the detail mask with the specified index. </param>
	void setMaskColorPath(int mask_index, const char *path);
	/// <summary> Returns a path to a source image containing the color data for the detail mask with the specified index.</summary>
	/// <param name='mask_index'> Index of the target detail mask.</param>
	/// <returns> Path to a color image containing the data for the detail mask with the specified index. </returns>
	const char *getMaskColorPath(int mask_index) const;
	/// <summary> Sets a path to a source image containing the opacity data for the detail mask with the specified index (1 channel). Opacity data is used for blending data between the layers. You can also specify an image channel to be used via the setMaskOpacityChannel(). </summary>
	/// <param name='mask_index'> Index of the target detail mask.</param>
	/// <param name='path'> Path to opacity map for the detail mask with the specified index (1-channel). </param>
	void setMaskOpacityPath(int mask_index, const char *path);
	/// <summary> Returns the path to a source image containing the opacity data for the detail mask with the specified index (1 channel). Opacity data is used for blending data between the layers.</summary>
	/// <param name='mask_index'> Index of the target detail mask.</param>
	/// <returns> Path to opacity map for the detail mask with the specified index (1-channel). </returns>
	const char *getMaskOpacityPath(int mask_index) const;
	/// <summary> Sets a new fade attenuation to be used for the data of the detail mask with the specified index. This parameter defines the distance of the transparency attenuation, starting from the edge of the map. </summary>
	/// <param name='mask_index'> Index of the target detail mask.</param>
	/// <param name='value'>Two-component vector (X, Y) defining fade attenuation of the detail mask data along X and Y axes.</param>
	void setMaskFadeAttenuation(int mask_index, const Unigine::Math::vec2 &value);
	/// <summary> Returns the current fade attenuation used for the data of the detail mask with the specified index. This parameter defines the distance of the transparency attenuation, starting from the edge of the map. </summary>
	/// <param name='mask_index'> Index of the desired detail mask.</param>
	/// <returns> Two-component vector (X, Y) defining fade attenuation of the detail mask with the specified index.</returns>
	Unigine::Math::vec2 getMaskFadeAttenuation(int mask_index) const;
	/// <summary> Sets the channel of the image from which the color data for the detail mask with the specified index is to be taken.</summary>
	/// <param name='mask_index'> Index of the desired detail mask.</param>
	/// <param name='channel'> Image channel to be used (see <see cref='CHANNEL'/>). </param>
	void setMaskColorChannel(int mask_index, LandscapeMapImportParameters::CHANNEL channel);
	/// <summary> Returns the channel of the image from which the color data for the detail mask with the specified index is taken.</summary>
	/// <param name='mask_index'> Index of the desired detail mask.</param>
	/// <returns> Current image channel (see <see cref='CHANNEL'/>). </returns>
	LandscapeMapImportParameters::CHANNEL getMaskColorChannel(int mask_index) const;
	/// <summary> Sets the channel of the image from which the opacity data for the detail mask with the specified index is to be taken. Opacity data is used for blending data between the layers.</summary>
	/// <param name='mask_index'> Index of the desired detail mask.</param>
	/// <param name='channel'> Image channel to be used (see <see cref='CHANNEL'/>). </param>
	void setMaskOpacityChannel(int mask_index, LandscapeMapImportParameters::CHANNEL channel);
	/// <summary> Returns the channel of the image from which the opacity data for the detail mask with the specified index is taken. Opacity data is used for blending data between the layers.</summary>
	/// <param name='mask_index'> Index of the desired detail mask.</param>
	/// <returns> Current image channel (see <see cref='CHANNEL'/>). </returns>
	LandscapeMapImportParameters::CHANNEL getMaskOpacityChannel(int mask_index) const;
	/// <summary> Sets a new blending mode to be used for the data of the detail mask with the specified index. Defines how the data of this layer is blended with underlying ones.</summary>
	/// <param name='mask_index'> Index of the target detail mask.</param>
	/// <param name='type'>New blending mode to be set for the detail mask (see <see cref='BLENDING_MODE'/>).</param>
	void setMaskBlendingMode(int mask_index, LandscapeMapImportParameters::BLENDING_MODE type);
	/// <summary> Returns the current blending mode used for the data of the detail mask with the specified index. Defines how the data of this layer is blended with underlying ones.</summary>
	/// <param name='mask_index'> Index of the desired detail mask.</param>
	/// <returns>Current blending mode used for the detail mask (see <see cref='BLENDING_MODE'/>).</returns>
	LandscapeMapImportParameters::BLENDING_MODE getMaskBlendingMode(int mask_index) const;
};
typedef Unigine::Ptr<LandscapeMapImportParameters> LandscapeMapImportParametersPtr;

} // namespace UnigineEditor
