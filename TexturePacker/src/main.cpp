#include "Parser.h"
#include "Packer.h"

struct ProgramArgs
{
	// Mandatory arguments
	const char* workingDirectory;
	const char* outputDirectory;
};

static ProgramArgs CreateArgs(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("Expected paths to WORKING and OUTPUT directories\n");
		std::abort();
	}

	if (argc > 3)
	{
		printf("Warning: too many arguments, expected paths to WORKING and OUTPUT directories\n");
	}

	return {
		argv[1],
		argv[2]
	};
}

int main(int argc, char** argv)
{
	ProgramArgs args = CreateArgs(argc, argv);

	if (!std::filesystem::exists(args.workingDirectory))
	{
		printf("Fatal: no such working directory exists (%s)\n", args.workingDirectory);
		return -1;
	}

	if (!std::filesystem::exists(args.outputDirectory))
	{
		printf("Info: output directory not found, create it (%s)\n", args.outputDirectory);

		const bool created = std::filesystem::create_directory(args.outputDirectory);
		if (!created)
		{
			printf("Fatal: cannot create output directory\n");
			return -1;
		}
	}

	Parser parser(args.workingDirectory);
	if (!parser.isReady())
	{
		printf("Fatal: parser exception\n");
		abort();
	}

	Packer packer(parser.parse(), args.outputDirectory);
	packer.generateAtlases();

	return 0;
}
