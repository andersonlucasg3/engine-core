using ProjectTools.Platforms;
using ProjectTools.Projects;

namespace Engine.Modules;

public class CoreModule : AModuleDefinition
{
    public override string Name => "Core";
    public override EModuleBinaryType BinaryType => EModuleBinaryType.DynamicLibrary;

    protected override void Configure(ATargetPlatform InTargetPlatform)
    {
        AddLinkWithLibrary(
            ETargetPlatform.Windows,
            "shell32.lib",
            "ole32.lib"
        );

        AddCompilerDefinition(
            ETargetPlatform.Android,
            "ANDROID_APPLICATION_PACKAGE",
            "\"com.cppmobileframework.helloworld\""
        );
    }
}