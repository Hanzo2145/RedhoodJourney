// Copyright belong to Anas (Hanzo) Hatachi

using UnrealBuildTool;
using System.Collections.Generic;

public class RedhoodJourneyEditorTarget : TargetRules
{
	public RedhoodJourneyEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "RedhoodJourney" } );
	}
}
