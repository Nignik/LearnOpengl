#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <cstdlib>

class FileSystem
{
private:
	using Builder = std::string(*) (const std::string& path);

public:
	static std::string getPath(const std::string& path)
	{
		static std::string(*pathBuilder)(std::string const&) = getPathBuilder();
		return (*pathBuilder)(path);
	}

private:
	static std::string const& getRoot()
	{
		static char const* envRoot = getenv("LOGL_ROOT_PATH");
		// Define a default root path if necessary; otherwise, use empty string
		static std::string root = (envRoot != nullptr ? envRoot : "");
		return root;
	}

	static Builder getPathBuilder()
	{
		if (!getRoot().empty())
			return &FileSystem::getPathRelativeRoot;
		else
			return &FileSystem::getPathRelativeBinary;
	}

	static std::string getPathRelativeRoot(const std::string& path)
	{
		return getRoot() + "/" + path;
	}

	static std::string getPathRelativeBinary(const std::string& path)
	{
		return "../../../" + path;
	}
};

#endif // FILESYSTEM_H