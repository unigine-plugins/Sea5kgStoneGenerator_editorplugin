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

#include <UnigineCallback.h>
#include <UnigineGUID.h>
#include <UniginePtr.h>

#include "UnigineEditorGlobal.h"
#include "UnigineCollection.h"

namespace UnigineEditor
{

class MountPointParameters;
//////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class is used to manage assets in the Editor. You can check if an asset with the specified GUID exists, get its file path, or subscribe for signals
/// to perform certain actions when an asset is added, moved, updated, or deleted.
/// AssetManager extends the functionality of UNIGINE's <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>File System</a>, being based on it. It performs operations itself while controlling the File System. Paths and GUIDs used for <b>Unigine::FileSystem</b> can be used for <b>UnigineEditor::AssetManager</b> as well. All paths returned by the AssetManager (via getAssetPaths, getDirectoryPaths, etc.) are virtual.
/// </summary>
class UNIGINE_EDITOR_API AssetManager
{
public:
	static int isInitialized();
	// assets
	/// <summary> Returns asset GUID for the specified asset path. This GUID can be used in calls to <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>Unigine::FileSystem</a>. Additional information for a given GUID can be obtained via the <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>Unigine::FileSystem</a> class.</summary>
	/// <param name='asset_path'> Path to the asset to retrieve a GUID for.</param>
	/// <returns> Asset GUID for the specified asset path.</returns>
	static Unigine::UGUID getAssetGUIDFromPath(const char *asset_path);
	/// <summary> Returns asset path for the specified asset GUID. </summary>
	/// <param name='asset_guid'> GUID of the asset to retrieve a path for.</param>
	/// <returns> Asset path for the specified asset GUID.</returns>
	static Unigine::String getAssetPathFromGUID(const Unigine::UGUID &asset_guid);
	/// <summary> Imports the specified asset with the specified set of import settings synchronously. The function call will not return until the blocking operation is complete, unlike the <see cref='importAssetAsync'/>() method. </summary>
	/// <param name='asset_path'> Path to the asset to be imported. This asset-file <u>MUST</u> be inside the <b>data_path</b> (or inside a registered mount point, which is actually the same). </param>
	/// <param name='import_parameters'> Set of import parameters for the asset.</param>
	/// <returns> <b>true</b> if the specified asset is imported successfully; otherwise, <b>false</b>.</returns>
	static bool importAssetSync(const char *asset_path, const Unigine::Ptr<Collection> &import_parameters = {});
	/// <summary> Imports the specified asset with the specified set of import settings asynchronously. The method is non-blocking and returns immediately, after calling it the operation is put in a queue, unlike the <see cref='importAssetSync'/>() method. </summary>
	/// <param name='asset_path'> Path to the asset to be imported. This asset-file <u>MUST</u> be inside the <b>data_path</b> (or inside a registered mount point, which is actually the same). </param>
	/// <param name='import_parameters'> Set of import parameters for the asset.</param>
	/// <returns> <b>true</b> if a new import task for the specified asset is successfully added to the queue; otherwise, <b>false</b>.</returns>
	static bool importAssetAsync(const char *asset_path, const Unigine::Ptr<Collection> &import_parameters = {});
	/// <summary> Reimports the specified asset with the specified set of import settings synchronously. The function call will not return until the blocking operation is complete, unlike the <see cref='reimportAssetAsync'/>() method. </summary>
	/// <param name='asset_path'>Path to the asset to be reimported.</param>
	/// <param name='import_parameters'> Set of import parameters for the asset.</param>
	/// <returns> <b>true</b> if the specified asset is reimported successfully; otherwise, <b>false</b>.</returns>
	static bool reimportAssetSync(const char *asset_path, const Unigine::Ptr<Collection> &import_parameters = {});
	/// <summary> Reimports the specified asset with the specified set of import settings asynchronously. The method is non-blocking and returns immediately, after calling it the operation is put in a queue, unlike the <see cref='reimportAssetSync'/>() method. </summary>
	/// <param name='asset_path'>Path to the asset to be reimported.</param>
	/// <param name='import_parameters'> Set of import parameters for the asset.</param>
	/// <returns> <b>true</b> if a new reimport task for the specified asset is successfully added to the queue; otherwise, <b>false</b>.</returns>
	static bool reimportAssetAsync(const char *asset_path, const Unigine::Ptr<Collection> &import_parameters = {});
	/// <summary> Removes the specified asset synchronously. The function call will not return until the blocking operation is complete, unlike the <see cref='removeAssetAsync'/>() method. </summary>
	/// <param name='asset_path'>Path to the asset to be removed.</param>
	/// <returns> <b>true</b> if the specified asset is removed successfully; otherwise, <b>false</b>.</returns>
	static bool removeAssetSync(const char *asset_path);
	/// <summary> Removes the specified asset asynchronously. The method is non-blocking and returns immediately, after calling it the operation is put in a queue, unlike the <see cref='removeAssetSync'/>() method. </summary>
	/// <param name='asset_path'>Path to the asset to be removed.</param>
	/// <returns> <b>true</b> if a new remove task for the specified asset is successfully added to the queue; otherwise, <b>false</b>.</returns>
	static bool removeAssetAsync(const char *asset_path);
	/// <summary> Moves the specified asset to a new location synchronously. The function call will not return until the blocking operation is complete, unlike the <see cref='moveAssetAsync'/>() method. </summary>
	/// <param name='old_asset_path'>Old asset path (FROM which the asset is moved).</param>
	/// <param name='new_asset_path'>New asset path (TO which the asset is moved).</param>
	/// <returns> <b>true</b> if the specified asset is successfully moved to the specified path; otherwise, <b>false</b>.</returns>
	static bool moveAssetSync(const char *old_asset_path, const char *new_asset_path);
	/// <summary> Moves the specified asset to a new location asynchronously. The method is non-blocking and returns immediately, after calling it the operation is put in a queue, unlike the <see cref='moveAssetSync'/>() method. </summary>
	/// <param name='old_asset_path'>Old asset path (FROM which the asset is moved).</param>
	/// <param name='new_asset_path'>New asset path (TO which the asset is moved).</param>
	/// <returns> <b>true</b> if a new move task for the specified asset and destination path is successfully added to the queue; otherwise, <b>false</b>.</returns>
	static bool moveAssetAsync(const char *old_asset_path, const char *new_asset_path);
	/// <summary> Renames the specified asset synchronously. The function call will not return until the blocking operation is complete, unlike the <see cref='renameAssetAsync'/>() method. </summary>
	/// <param name='asset_path'>Path to the asset to be renamed.</param>
	/// <param name='new_asset_name'>New asset name.</param>
	/// <returns> <b>true</b> if the specified asset is renamed successfully; otherwise, <b>false</b>.</returns>
	static bool renameAssetSync(const char *asset_path, const char *new_asset_name);
	/// <summary> Renames the specified asset asynchronously. The method is non-blocking and returns immediately, after calling it the operation is put in a queue, unlike the <see cref='renameAssetSync'/>() method. </summary>
	/// <param name='asset_path'>Path to the asset to be renamed.</param>
	/// <param name='new_asset_name'>New asset name.</param>
	/// <returns> <b>true</b> if a new rename task for the specified asset is successfully added to the queue; otherwise, <b>false</b>.</returns>
	static bool renameAssetAsync(const char *asset_path, const char *new_asset_name);
	/// <summary> Copies the specified asset to the specified destination path synchronously. The function call will not return until the blocking operation is complete, unlike the <see cref='copyAssetAsync'/>() method. </summary>
	/// <param name='asset_path'>Path to the asset to be copied.</param>
	/// <param name='new_asset_path'>Destination path to which the asset is to be copied.</param>
	/// <returns> <b>true</b> if the specified asset is successfully copied to the specified destination path; otherwise, <b>false</b>.</returns>
	static bool copyAssetSync(const char *asset_path, const char *new_asset_path);
	/// <summary> Copies the specified asset to the specified destination path asynchronously. The method is non-blocking and returns immediately, after calling it the operation is put in a queue, unlike the <see cref='copyAssetSync'/>() method. </summary>
	/// <param name='asset_path'>Path to the asset to be copied.</param>
	/// <param name='new_asset_path'>Destination path to which the asset is to be copied.</param>
	/// <returns> <b>true</b> if a new copy task for the specified asset and destination path is successfully added to the queue; otherwise, <b>false</b>.</returns>
	static bool copyAssetAsync(const char *asset_path, const char *new_asset_path);
	/// <summary> Returns a value indicating whether an asset with the specified file path exists. </summary>
	/// <param name='asset_path'>Path of the asset to be checked.</param>
	/// <returns> <b>true</b> if an asset with the specified file path exists; otherwise, <b>false</b>.</returns>
	static bool isAsset(const char *asset_path);
	/// <summary> Returns the set of import parameters for the specified asset path. </summary>
	/// <param name='asset_path'>Path of the asset to be checked.</param>
	/// <returns> Import parameters for the specified asset path on success; or <b>nullptr</b>, if an error has occurred.</returns>
	static Unigine::Ptr<Collection> getAssetImportParameters(const char *asset_path);
	/// <summary> Returns a value indicating whether the asset with the specified file path can be updated (writing operation is enabled for it). </summary>
	/// <param name='asset_path'>Asset path to be checked.</param>
	/// <returns> <b>true</b> if the asset with the specified file path can be updated; otherwise, <b>false</b>.</returns>
	static bool isAssetWritable(const char *asset_path);
	/// <summary> Returns the list of GUIDs for all assets in the root project directory (including all subdirectories). These GUIDs can be used in calls to <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>Unigine::FileSystem</a>. Additional information for a given GUID can be obtained via the <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>Unigine::FileSystem</a> class.</summary>
	/// <returns>The list of GUIDs for all assets in the root project directory (including all subdirectories).</returns>
	static Unigine::Vector<Unigine::UGUID> getAssetGUIDs();
	/// <summary> Saves to the vector specified as the argument GUIDs for all assets in the root project directory (including all subdirectories). These GUIDs can be used in calls to <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>Unigine::FileSystem</a>. Additional information for a given GUID can be obtained via the <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>Unigine::FileSystem</a> class.</summary>
	/// <param name='asset_guids'>The vector to store GUIDs for all assets in the root project directory (including all subdirectories).</param>
	static void getAssetGUIDs(Unigine::Vector<Unigine::UGUID> &asset_guids);
	/// <summary> Returns the list of paths for all assets in the root project directory (including all subdirectories). </summary>
	/// <returns>The list of paths for all assets in the root project directory (including all subdirectories).</returns>
	static Unigine::Vector<Unigine::String> getAssetPaths();
	/// <summary> Saves to the vector specified as the argument the list of paths for all assets in the root project directory (including all subdirectories). </summary>
	/// <param name='asset_paths'>The vector to store paths for all assets in the root project directory (including all subdirectories).</param>
	static void getAssetPaths(Unigine::Vector<Unigine::String> &asset_paths);
	/// <summary> Returns the list of GUIDs for all assets in the specified directory (including all subdirectories). Thess GUIDs can be used in calls to <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>Unigine::FileSystem</a>. Additional information for a given GUID can be obtained via the <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>Unigine::FileSystem</a> class. </summary>
	/// <param name='directory_path'>Directory path for which all asset GUIDs are to be retrieved.</param>
	/// <returns>The list of GUIDs for all assets in the specified directory (including all subdirectories).</returns>
	static Unigine::Vector<Unigine::UGUID> getAssetGUIDsForDirectory(const char *directory_path);
	/// <summary> Saves to the vector specified as the argument the list of GUIDs for all assets in the specified directory (including all subdirectories). Thess GUIDs can be used in calls to <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>Unigine::FileSystem</a>. Additional information for a given GUID can be obtained via the <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>Unigine::FileSystem</a> class. </summary>
	/// <param name='directory_path'>Directory path for which all asset GUIDs are to be retrieved.</param>
	/// <param name='asset_guids'>The vector to store GUIDs for all assets in the specified directory (including all subdirectories).</param>
	static void getAssetGUIDsForDirectory(const char *directory_path, Unigine::Vector<Unigine::UGUID> &asset_guids);
	/// <summary> Returns the list of paths for all assets in the specified directory (including all subdirectories). </summary>
	/// <param name='directory_path'>Directory path for which all asset paths are to be retrieved.</param>
	/// <returns>The list of paths for all assets in the specified directory (including all subdirectories).</returns>
	static Unigine::Vector<Unigine::String> getAssetPathsForDirectory(const char *directory_path);
	/// <summary> Saves to the vector specified as the argument the list of paths for all assets in the specified directory (including all subdirectories). </summary>
	/// <param name='directory_path'>Directory path for which all asset paths are to be retrieved.</param>
	/// <param name='asset_paths'>The vector to store paths for all assets in the specified directory (including all subdirectories).</param>
	static void getAssetPathsForDirectory(const char *directory_path, Unigine::Vector<Unigine::String> &asset_paths);
	/// <summary> Returns the list of all runtime GUIDs for the specified asset path (some assets, like FBX-containers may produce multiple runtimes on importing). Thess GUIDs can be used in calls to <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>Unigine::FileSystem</a>. Additional information for a given GUID can be obtained via the <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>Unigine::FileSystem</a> class. </summary>
	/// <param name='asset_path'>Asset path for which the list of runtime GUIDs is to be retrieved.</param>
	/// <returns>The list of all runtime GUIDs for the specified asset path.</returns>
	static Unigine::Vector<Unigine::UGUID> getRuntimeGUIDs(const char *asset_path);
	/// <summary> Saves to the vector specified as the argument the list of all runtime GUIDs for the specified asset path (some assets, like FBX-containers may produce multiple runtimes on importing). Thess GUIDs can be used in calls to <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>Unigine::FileSystem</a>. Additional information for a given GUID can be obtained via the <a href='https://developer.unigine.com/en/docs/latest/api/library/filesystem/class.filesystem'>Unigine::FileSystem</a> class. </summary>
	/// <param name='asset_path'>Asset path for which the list of runtime GUIDs is to be retrieved.</param>
	/// <param name='runtime_guids'>The vector to store all runtime GUIDs for the specified asset path.</param>
	static void getRuntimeGUIDs(const char *asset_path, Unigine::Vector<Unigine::UGUID> &runtime_guids);
	/// <summary> Returns an alias used for the runtime with the specified GUID. </summary>
	/// <param name='runtime_guid'>Runtime GUID for which the alias is to be retrieved.</param>
	/// <returns>The alias used for the runtime with the specified GUID.</returns>
	static Unigine::String getRuntimeAlias(const Unigine::UGUID &runtime_guid);
	/// <summary> Returns a value indicating whether the runtime with the specified GUID is a primary one. </summary>
	/// <param name='runtime_guid'>Runtime GUID to be checked.</param>
	/// <returns> <b>true</b> if the runtime with the specified GUID is a primary one; otherwise, <b>false</b>.</returns>
	static bool isRuntimePrimary(const Unigine::UGUID &runtime_guid);
	// directories
	/// <summary> Creates a new directory. The function will create all parent directories necessary to create the directory specified.</summary>
	/// <param name='directory_path'>New directory path to be created.</param>
	/// <returns> <b>true</b> if the specified directory is created successfully or already exists when this method is called; otherwise, <b>false</b> (including the case when the specified directory path exists in a read-only mount).</returns>
	static bool createDirectory(const char *directory_path);
	/// <summary> Removes the specified directory synchronously. The function call will not return until the blocking operation is complete, unlike the <see cref='removeDirectoryAsync'/>() method. </summary>
	/// <param name='directory_path'>Directory path to be removed.</param>
	/// <returns> <b>true</b> if the specified directory is removed successfully; otherwise, <b>false</b>.</returns>
	static bool removeDirectorySync(const char *directory_path);
	/// <summary> Removes the specified directory asynchronously. The method is non-blocking and returns immediately, after calling it the operation is put in a queue, unlike the <see cref='removeDirectorySync'/>() method. </summary>
	/// <param name='directory_path'>Directory path to be removed.</param>
	/// <returns> <b>true</b> if the specified directory is removed successfully; otherwise, <b>false</b>.</returns>
	static bool removeDirectoryAsync(const char *directory_path);
	/// <summary> Moves the specified directory to a new location synchronously. The function call will not return until the blocking operation is complete, unlike the <see cref='moveDirectoryAsync'/>() method. </summary>
	/// <param name='old_directory_path'>Old directory path (FROM which the directory is moved).</param>
	/// <param name='new_directory_path'>New directory path (TO which the directory is moved).</param>
	/// <returns> <b>true</b> if the specified directory is successfully moved to the specified path; otherwise, <b>false</b>.</returns>
	static bool moveDirectorySync(const char *old_directory_path, const char *new_directory_path);
	/// <summary> Moves the specified directory to a new location asynchronously. The method is non-blocking and returns immediately, after calling it the operation is put in a queue, unlike the <see cref='moveDirectorySync'/>() method. </summary>
	/// <param name='old_directory_path'>Old directory path (FROM which the directory is moved).</param>
	/// <param name='new_directory_path'>New directory path (TO which the directory is moved).</param>
	/// <returns> <b>true</b> if the specified directory is successfully moved to the specified path; otherwise, <b>false</b>.</returns>
	static bool moveDirectoryAsync(const char *old_directory_path, const char *new_directory_path);
	/// <summary> Renames the specified directory synchronously. The function call will not return until the blocking operation is complete, unlike the <see cref='renameDirectoryAsync'/>() method. </summary>
	/// <param name='directory_path'>Path to the directory to be renamed.</param>
	/// <param name='new_directory_name'>New directory name.</param>
	/// <returns> <b>true</b> if the specified directory is renamed successfully; otherwise, <b>false</b>.</returns>
	static bool renameDirectorySync(const char *directory_path, const char *new_directory_name);
	/// <summary> Renames the specified directory asynchronously. The method is non-blocking and returns immediately, after calling it the operation is put in a queue, unlike the <see cref='renameDirectorySync'/>() method. </summary>
	/// <param name='directory_path'>Path to the directory to be renamed.</param>
	/// <param name='new_directory_name'>New directory name.</param>
	/// <returns> <b>true</b> if the specified directory is renamed successfully; otherwise, <b>false</b>.</returns>
	static bool renameDirectoryAsync(const char *directory_path, const char *new_directory_name);
	/// <summary> Copies the specified directory to the specified destination path synchronously. The function call will not return until the blocking operation is complete, unlike the <see cref='copyDirectoryAsync'/>() method. </summary>
	/// <param name='directory_path'>Path to the directory to be copied.</param>
	/// <param name='new_directory_path'>Destination path to which the directory is to be copied.</param>
	/// <returns> <b>true</b> if the specified directory is successfully copied to the specified destination path; otherwise, <b>false</b>.</returns>
	static bool copyDirectorySync(const char *directory_path, const char *new_directory_path);
	/// <summary> Copies the specified directory to the specified destination path asynchronously. The method is non-blocking and returns immediately, after calling it the operation is put in a queue, unlike the <see cref='copyDirectorySync'/>() method. </summary>
	/// <param name='directory_path'>Path to the directory to be copied.</param>
	/// <param name='new_directory_path'>New directory name.</param>
	/// <returns> <b>true</b> if the specified directory is successfully copied to the specified destination path; otherwise, <b>false</b>.</returns>
	static bool copyDirectoryAsync(const char *directory_path, const char *new_directory_path);
	/// <summary> Returns a value indicating whether the specified directory path exists. </summary>
	/// <param name='directory_path'>Directory path to be checked.</param>
	/// <returns> <b>true</b> if the specified directory exists; otherwise, <b>false</b>.</returns>
	static bool isDirectory(const char *directory_path);
	/// <summary> Returns a value indicating whether the specified directory path is writable. </summary>
	/// <param name='directory_path'>Directory path to be checked.</param>
	/// <returns> <b>true</b> if the specified directory path is writable; otherwise, <b>false</b>.</returns>
	static bool isDirectoryWritable(const char *directory_path);
	/// <summary> Returns the list of all subdirectories for the root project directory. </summary>
	/// <returns> The list of all subdirectories for the root project directory.</returns>
	static Unigine::Vector<Unigine::String> getDirectoryPathsAll();
	/// <summary> Saves to the vector specified as the argument the list of all subdirectories for the root project directory. </summary>
	/// <param name='directory_paths'> The vector to store all subdirectories for the root project directory.</param>
	static void getDirectoryPathsAll(Unigine::Vector<Unigine::String> &directory_paths);
	/// <summary> Returns the list of all subdirectories for the specified directory path. </summary>
	/// <param name='directory_path'>Directory path.</param>
	/// <returns> The list of all subdirectories for the specified directory path.</returns>
	static Unigine::Vector<Unigine::String> getDirectoryPaths(const char *directory_path);
	/// <summary> Saves to the vector specified as the argument the list of all subdirectories for the specified directory path. </summary>
	/// <param name='directory_path'>Directory path.</param>
	/// <param name='directory_paths'> The vector to store all subdirectories for the specified directory path.</param>
	static void getDirectoryPaths(const char *directory_path, Unigine::Vector<Unigine::String> &directory_paths);
	// mount points
	/// <summary> Creates a new mount point for the specified path applying the specified parameters (access mode, filters, etc.) and the corresponding <b>.umount</b> file. </summary>
	/// <param name='directory_path'>Path to the directory to be mounted.</param>
	/// <param name='mount_creation_parameters'>Parameters of the mount point to be created (access mode, filters, etc.).</param>
	/// <returns> <b>true</b> if the mount point is created successfully; otherwise, <b>false</b>.</returns>
	static bool createMountPoint(const char *directory_path, const Unigine::Ptr<MountPointParameters> &mount_creation_parameters);
	/// <summary> Unmounts the mount point for the specified path and deletes the corresponding <b>.umount</b> file. </summary>
	/// <param name='directory_path'>Mount path to be removed.</param>
	/// <returns> <b>true</b> if the mount point is removed successfully; otherwise, <b>false</b>.</returns>
	static bool removeMountPoint(const char *directory_path);
	/// <summary> Returns a value indicating whether a mount point with the specified path exists. </summary>
	/// <param name='directory_path'>Directory path to be checked.</param>
	/// <returns> <b>true</b> if the mount point exists; otherwise, <b>false</b>.</returns>
	static bool isMountPoint(const char *directory_path);
	/// <summary> Returns the parameters for the specified mount point (access mode, filters, etc.) as an instance of the <see cref='MountPointParameters'/> class). </summary>
	/// <param name='directory_path'>Path to the mounted directory.</param>
	/// <returns> Parameters of the mount point on success; otherwise, <b>nullptr</b> if an error has occurred.</returns>
	static Unigine::Ptr<MountPointParameters> getMountPointParameters(const char *directory_path);
	/// <summary> Reloads the data and updates the mount point with the specified path asynchronously. After calling this method the operation is put in a queue.</summary>
	/// <param name='directory_path'>Directory path for the mount point to be refreshed.</param>
	/// <returns> <b>true</b> if the mount point is refreshed successfully; otherwise, <b>false</b>.</returns>
	static bool refreshMountPointAsync(const char *directory_path);
	// file system watcher
	/// <summary> Increments an internal counter which is used to determine whether to allow automatic refreshing of the assets database
	/// (i.e. automatic reimporting of changed assets). When building your own Editor tools, you can use this method together with
	/// unblockAutoRefresh() to prevent an auto-refreshing from happening during certain operations (e.g. if you are building a custom
	/// integration with a version control system). This method does not simply enable the auto-refresh feature. Instead, it increments a counter,
	/// and only allows auto-refresh when the counter reaches zero. Therefore, each time you call blockAutoRefresh(), you must make sure
	/// you also make a corresponding call to unblockAutoRefresh(). This internal counter is used so that if your code executes multiple
	/// nested 'block' and 'unblock' pairs, the inner pairs do not accidentally re-enable auto-refresh too early. Instead, each pair increments
	/// and decrements the counter by one, and if your code is correctly nested, the final outer call to unblockAutoRefresh() sets the counter to zero.</summary>
	static void blockAutoRefresh();
	/// <summary> Decrements an internal counter which is used to determine whether to allow automatic refreshing of the assets database
	/// (i.e. automatic reimporting of changed assets). When building your own Editor tools, you can use this method together with
	/// blockAutoRefresh() to prevent an auto-refreshing from happening during certain operations (e.g. if you are building a custom
	/// integration with a version control system). This method does not simply enable the auto-refresh feature. Instead, it decrements a counter,
	/// and only allows auto-refresh when the counter reaches zero. It is designed to be used to re-enable auto-refresh after a call to
	/// blockAutoRefresh() previously disabled it. This internal counter is used so that if your code executes multiple
	/// nested 'block' and 'unblock' pairs, the inner pairs do not accidentally re-enable auto-refresh too early. Instead, each pair increments
	/// and decrements the counter by one, and if your code is correctly nested, the final outer call to unblockAutoRefresh() sets the counter to zero.</summary>
	static void unblockAutoRefresh();
	/// <summary> Returns a value indicating whether automatic refreshing of the assets database is currently blocked or not
	/// (i.e. automatic reimporting of changed assets). When building your own Editor tools, you can use blockAutoRefresh() together with
	/// unblockAutoRefresh() to prevent an auto-refreshing from happening during certain operations (e.g. if you are building a custom
	/// integration with a version control system). The system does not simply enable/disable the auto-refresh feature. Instead,
	/// it increments (see <see cref='unblockAutoRefresh'/>) and decrements (see <see cref='blockAutoRefresh'/>) a counter, and only allows
	/// auto-refresh when the counter reaches zero. This internal counter is used so that if your code executes multiple
	/// nested 'block' and 'unblock' pairs, the inner pairs do not accidentally re-enable auto-refresh too early. Instead, each pair increments
	/// and decrements the counter by one, and if your code is correctly nested, the final outer call to unblockAutoRefresh() sets the counter to zero.</summary>
	static bool isAutoRefreshBlocked();
	// asset events
	/// <summary> This event may be called upon either of the following occurs:
	/// <ol>
		/// <li>The asset has been copied. After the asset has been copied, AssetManager notifies via this event that a new asset has been added.</li>
		/// <li>The user has added a new asset to the folders tracked by the Editor while the Editor is running.</li>
	/// </ol>
	///</summary>
	static Unigine::Event<const char *> &getEventAssetAdded();
	/// <summary> While this event is called, the information on the asset being deleted (such as 'getAssetImportParameters()') is still accessible via the AssetManager API.</summary>
	static Unigine::Event<const char *> &getEventAssetBeforeRemove();
	/// <summary> The event is called when the asset is removed.</summary>
	static Unigine::Event<const char *> &getEventAssetRemoved();
	/// <summary> The event is called when the asset has been changed OR the parameters of the meta have been changed, which caused the asset reimport and/or the meta file update.</summary>
	static Unigine::Event<const char *> &getEventAssetChanged();
	/// <summary> The event is called when the asset has been moved or renamed.</summary>
	static Unigine::Event<const char *, const char *> &getEventAssetMoved();
	// directory events
	/// <summary> The event is called when a new directory has been added.</summary>
	static Unigine::Event<const char *> &getEventDirectoryAdded();
	/// <summary> While this event is called, the information on the directory being deleted (such as 'isDirectoryWritable()') is still accessible via the AssetManager API.</summary>
	static Unigine::Event<const char *> &getEventDirectoryBeforeRemove();
	/// <summary> The event is called when the directory is removed.</summary>
	static Unigine::Event<const char *> &getEventDirectoryRemoved();
	/// <summary> The event is called when the directory has been moved or renamed.</summary>
	static Unigine::Event<const char *, const char *> &getEventDirectoryMoved();
	// process events
	/// <summary> The event is called when AssetManager has started asynchronous processing assets or directories that have been added, changed, moved, renamed, or deleted.</summary>
	static Unigine::Event<> &getEventProcessBegin();
	/// <summary> The event is called when AssetManager has finished asynchronous processing assets or directories that have been added, changed, moved, renamed, or deleted.</summary>
	static Unigine::Event<> &getEventProcessEnd();
	// utils
	/// <summary> Generates a unique path which is not currently used in the File System for the specified path. Unique paths for files having an extension shall be generated without affecting the extension: <em>folder/file.png -> folder/file_0.png</em>. </summary>
	/// <returns> Unique generated file system path for the specified path on success, or an <b>empty string</b> in the following cases:
	/// <ol>
		/// <li>Specified path is empty</li>
		/// <li>Specified path points somewhere outside the data folder and mount points</li>
		/// <li>Root folder of the specified path is known to be read-only. </li>
	/// </ol>
	/// </returns>
	static Unigine::String generateUniqueWritablePath(const char *path);
	/// <summary> Checks if the specified path exists, either it is registered in the Asset System (it is an asset, a folder, or a mount point), or it is an existing file in the File System which is not added to Asset System for some reason (e.g., its name or extension is forbidden or filtered out by exclusive or ignore filters). </summary>
	/// <returns> <b>true</b> if the specified path exists; otherwise, <b>false</b>. </returns>
	static bool isExist(const char *path);
};


/// <summary> This class is used to manage parameters of mount points, such as access, path, filters. Mount points are used to extend the Engine's file system. Mount point is a sort of a symlink enabling you to extend the virtual file system of your project by adding any external folders and packages to the 'data' directory.</summary>
class UNIGINE_EDITOR_API MountPointParameters : public Unigine::APIInterface
{
public:

	/// <summary> Access mode.</summary>
	enum ACCESS
	{
		/// <summary> Read-only mode. The mount point is read-only, files contained in the mounted folder/package cannot be modified.</summary>
		ACCESS_READONLY = 0,
		/// <summary> Read-write mode. The mount point access mode is read-write, files contained in the mounted folder/package can be modified.</summary>
		ACCESS_READWRITE,
	};
	/// <summary> Creates a new instance of the class.</summary>
	static Unigine::Ptr<MountPointParameters> create();
	/// <summary> Sets access mode for the mount point.</summary>
	/// <param name='access'> New access mode to be set (see <see cref='ACCESS'/>).</param>
	void setAccess(MountPointParameters::ACCESS access);
	/// <summary> Sets access mode for the mount point.</summary>
	MountPointParameters::ACCESS getAccess() const;
	/// <summary> Sets the absolute path to the mounted folder/package.</summary>
	/// <param name='path'> New absolute path to be set.</param>
	void setAbsolutePath(const char *path);
	/// <summary> Returns the absolute path to the mounted folder/package.</summary>
	const char *getAbsolutePath() const;
	/// <summary> Adds a new item to the list of exclusive filters (whitelist) to be used for files as a list of wildcards (e.g., '*.jpg', 'some_folder_*').
	/// This list is used to selectively add files of certain types or contents of folders with certain names.</summary>
	/// <param name='exclusive_filter'>New exclusive filter item to be added (as a list of wildcards).</param>
	void addExclusiveFilter(const char *exclusive_filter);
	/// <summary> Returns the whole list of currently used exclusive filters (as a list of wildcards).
	/// This whitelist is used to selectively add files of certain types or contents of folders with certain names.</summary>
	/// <returns> The whole list of currently used exclusive filters (as a list of wildcards). </returns>
	Unigine::Vector<Unigine::String> getExclusiveFilters() const;
	/// <summary> Saves to the vector specified as the argument the whole list of currently used exclusive filters (as a list of wildcards).
	/// This whitelist is used to selectively add files of certain types or contents of folders with certain names.</summary>
	/// <param name='exclusive_filters'> The whole list of currently used exclusive filters (as a list of wildcards). </param>
	void getExclusiveFilters(Unigine::Vector<Unigine::String> &exclusive_filters) const;
	/// <summary> Adds a new item to the list of ignore filters (blacklist) to be used for files as a list of wildcards (e.g., '*.jpg', 'some_folder_*').
	/// This list is used to selectively ignore files of certain types or contents of folders with certain names.</summary>
	/// <param name='ignore_filter'>New ignore filter item to be added (as a list of wildcards).</param>
	void addIgnoreFilter(const char *ignore_filter);
	/// <summary> Returns the whole list of currently used ignore filters (as a list of wildcards).
	/// This blacklist is used to selectively ignore files of certain types or contents of folders with certain names.</summary>
	/// <returns> The whole list of currently used ignore filters (as a list of wildcards). </returns>
	Unigine::Vector<Unigine::String> getIgnoreFilters() const;
	/// <summary> Saves to the vector specified as the whole list of currently used ignore filters (as a list of wildcards).
	/// This blacklist is used to selectively ignore files of certain types or contents of folders with certain names.</summary>
	/// <param name='ignore_filters'> The whole list of currently used ignore filters (as a list of wildcards). </param>
	void getIgnoreFilters(Unigine::Vector<Unigine::String> &ignore_filters) const;
};
typedef Unigine::Ptr<MountPointParameters> MountPointParametersPtr;

} // namespace UnigineEditor
