// Copyright belong to Anas (Hanzo) Hatachi

using UnrealBuildTool;
using System.Collections.Generic;

public class RedhoodJourneyTarget : TargetRules
{
	public RedhoodJourneyTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "RedhoodJourney" } );
	}
}
