Scriptname EzF4sePluginExampleQuestScript extends Quest
{f4se Plugin Example Quest Script}

; ========================================================
; IMPORTS ================================================
; ========================================================

import EzF4seTestClass

; ========================================================
; VARIABLES ==============================================
; ========================================================

Int Property intTest = 1 Auto

Float Property floatTest = 1.0 Auto

Bool Property boolTest = False Auto

String Property stringTest = "One" Auto

; ========================================================
; EVENTS =================================================
; ========================================================

Event OnQuestInit()
	Debug.Trace(self +" OnQuestInit()")
	Debug.Notification("EzF4sePluginExampleQuest : OnQuestInit")
	Debug.MessageBox("EzF4sePluginExampleQuest : OnQuestInit")
	
	;code here
	
	;EzF4seTestClass
	;EzF4seTestClass.Test();
	
	if (EzF4seTestClass.Test())
		Debug.Trace(self +" EzF4seTestClass.Test()")
		Debug.Notification("EzF4sePluginExampleQuest : EzF4seTestClass.Test()")
		Debug.MessageBox("EzF4sePluginExampleQuest : EzF4seTestClass.Test()")
	endif
	
	if (Test())
		Debug.Trace(self +" Test()")
		Debug.Notification("EzF4sePluginExampleQuest : Test()")
		Debug.MessageBox("EzF4sePluginExampleQuest : Test()")
	endif
	
	
	Debug.Trace(self +" OnQuestInit() : EOL")
	Debug.Notification("EzF4sePluginExampleQuest : OnQuestInit : EOL")
	Debug.MessageBox("EzF4sePluginExampleQuest : OnQuestInit : EOL")
EndEvent

Event OnReset()
	Debug.Trace(self +" OnReset()")
	Debug.Notification("EzF4sePluginExampleQuest : OnReset")
	Debug.MessageBox("EzF4sePluginExampleQuest : OnReset")
	
	;code here
	
	Debug.Trace(self +" OnReset() : EOL")
	Debug.Notification("EzF4sePluginExampleQuest : OnReset : EOL")
EndEvent

Event OnQuestShutdown()
	Debug.Trace(self +" OnQuestShutdown()")
	Debug.Notification("EzF4sePluginExampleQuest : OnQuestShutdown")
	Debug.MessageBox("EzF4sePluginExampleQuest : OnQuestShutdown")
	
	;code here
	
	Debug.Trace(self +" OnQuestShutdown() : EOL")
	Debug.Notification("EzF4sePluginExampleQuest : OnQuestShutdown : EOL")
EndEvent

