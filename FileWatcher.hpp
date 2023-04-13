#pragma once
#include <filesystem>
#include <thread>
#include <memory>
#include <functional>
#include <optional>
#include <assert.h>
#include <system_error>

enum class EFileWatcherError
{
	Unknown = 0,
	InvalidFile,
	SpecifiedFileDoesntExist,
	RegularFileHasNoParentDirectory,
	InternalStateCreationFailed,
	WatchedDirectoryWasDeleted,
	FailedWatchingSubdirectory,
};

class FileWatcherErrorCategory final : public std::error_category
{
private:
	constexpr FileWatcherErrorCategory(const FileWatcherErrorCategory&) noexcept = delete;
	constexpr FileWatcherErrorCategory(FileWatcherErrorCategory&&) noexcept = delete;
	constexpr FileWatcherErrorCategory& operator=(const FileWatcherErrorCategory&) noexcept = delete;
	constexpr FileWatcherErrorCategory& operator=(FileWatcherErrorCategory&&) noexcept = delete;
public:
	FileWatcherErrorCategory() noexcept = default;
	constexpr const char* name() const noexcept override final
	{
		return "File Watcher Category";
	}

	constexpr std::string message(const int errorCode) const noexcept override final
	{
		switch (static_cast<EFileWatcherError>(errorCode))
		{
		case EFileWatcherError::InvalidFile: 						return "Specified file is invalid";
		case EFileWatcherError::SpecifiedFileDoesntExist: 			return "Specified file doesn't exist";
		case EFileWatcherError::RegularFileHasNoParentDirectory: 	return "Specified file is regular but has no parent directory";
		case EFileWatcherError::InternalStateCreationFailed: 		return "Internal state creation failed";
		case EFileWatcherError::WatchedDirectoryWasDeleted:			return "Watched directory was deleted, moved or unmounted. If the specified target was a regular file, the parent directory is invalid";
		case EFileWatcherError::FailedWatchingSubdirectory:			return "Failed to watch a subdirectory";
		[[unlikely]] default:
			assert(false);
			break;
		}

		assert(false);
		return "Unknown";
	}
} const fileWatcherErrorCategory;

inline const FileWatcherErrorCategory& FileWatcherCategory() noexcept
{
	return fileWatcherErrorCategory;
}

/**
 * Enum class representing all the possible file actions
 */
enum class EFileAction
{
	Error,
	Created,
	Deleted,
	Modified,
	Renamed,
};

/**
 * Converts an EFileAction enum value to it's string representation.
 * @param fileAction the file action to stringify.
 */
constexpr const char* FileActionToString(const EFileAction fileAction) noexcept
{
	switch (fileAction)
	{
	case EFileAction::Error:		return "Error";
	case EFileAction::Created:		return "Created";
	case EFileAction::Deleted:		return "Deleted";
	case EFileAction::Modified:		return "Modified";
	case EFileAction::Renamed:		return "Renamed";

		[[unlikely]]
	default:
		assert(false);
		break;
	};

	assert(false);
	return "UNKNOWN";
}

/**
 * @param Full path to file (new value if renamed).
 * @param Full path to file if it was renamed (old value), else is left out.
 * @param Type of file action that had occurred. EFileAction::Error is returned if an error had occurred.
 * @param Nonzero populated error code if an error had occurred.
 */
using FileWatcherCallback = std::function<void(std::filesystem::path, std::optional<std::filesystem::path>, EFileAction, std::error_code)>;

/**
 * File watcher class. Can be used to monitor either an existing directory recursively or a specific file.
 * If the file doesn't exist, the watcher will listen for it's creation based on it's path.
 */
class FileWatcher
{
public:
	constexpr FileWatcher(const FileWatcher&) = delete;
	constexpr FileWatcher& operator=(const FileWatcher&) = delete;

	/**
	 * File Watcher constructor.
	 * @param observedPath - Path to observed target. Can be either a filepath or directory path.
	 * @param callback - Callback function.
	 * @param returnAbsolutePath - If true, returns target concatenated directory to absolute path.
	 * @param error - error code, populated on failure.
	 */
	explicit FileWatcher(const std::filesystem::path& observedPath, FileWatcherCallback&& callback, const bool returnAbsolutePath, std::error_code& error) noexcept;

	/**
	 * File Watcher constructor.
	 * @param observedPath - Path to observed target. Can be either a filepath or directory path.
	 * @param callback - Callback function.
	 * @param returnAbsolutePath - If true, returns target concatenated directory to absolute path.
	 * @param error - error code, populated on failure.
	 */
	explicit FileWatcher(const std::filesystem::path& observedPath, const FileWatcherCallback& callback, const bool returnAbsolutePath, std::error_code& error) noexcept;

	/**
	 * File watcher destructor.
	 */
	~FileWatcher() noexcept;

	/**
	 * Returns true if the file watcher is actively monitoring the target.
	 */
	[[nodiscard]] bool IsWatching() const noexcept;
private:
	void SetupWatcher(const bool useAsbolutePath, std::error_code& error) noexcept;
	void WatcherThreadWork() const noexcept;

	[[nodiscard]] std::filesystem::path ConstructReturnPath(struct FilewatcherCharacterType* fileNameBuffer, const size_t) const noexcept;
private:
	mutable std::atomic<bool> m_IsWatching;		// true if actively watching.
	std::filesystem::path m_ObservedPath;		// path of observed directory (parent path if observing a file).
	std::filesystem::path m_ObservedFile; 		// empty if observing a directory.
	FileWatcherCallback m_Callback;

	std::thread m_WatcherThread;				// watching is performed on a separate blocking thread.
	std::unique_ptr<struct FileWatcherInternalState> m_InternalState;
private:
	constexpr static inline size_t s_WatchBufferSize{ 8192U };
};