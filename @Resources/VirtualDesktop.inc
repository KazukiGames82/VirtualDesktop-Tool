;----------------------------------------------------------------------
; Script that can return total and current desktop(s).

; LinkToDesktopIDS need the name of a registry measure with the next params:
; [<>]
; RegHKey=HKEY_CURRENT_USER 
; RegKey=Software\Microsoft\Windows\CurrentVersion\Explorer\VirtualDesktops
; RegValue=VirtualDesktopIDs
; RegExpSubstitute=1
; Substitute="(.{32})":"\1 "

; LinkToCurrentDesktop need the name of a registry measure with the next params:
; [<>]
; RegHKey=HKEY_CURRENT_USER
; For Windows 10:
; RegKey=Software\Microsoft\Windows\CurrentVersion\Explorer\SessionInfo\[&Measure_Current_Session]\VirtualDesktops
; For Windows 11:
; RegKey=Software\Microsoft\Windows\CurrentVersion\Explorer\VirtualDesktops
; RegValue=CurrentVirtualDesktop

; Available Functions:
; Get Total Desktops = [&Measure_Script:GetDesktopCount()]
; Get Curremt Desktops = [&Measure_Script:GetCurrentDesktop()]

[Measure_Script]
Measure=Script
ScriptFile=#@#\Scripts\Desktop.lua
LinkToDesktopIDS=Measure_Desktop_Count
LinkToCurrentDesktop=Measure_Current_Desktop
Group=VirtualDesktopMeasures
UpdateDivider=-1

;----------------------------------------------------------------------
; Measure for <LinkToDesktopIDS>
[Measure_Desktop_Count]
Measure=Registry
RegHKey=HKEY_CURRENT_USER 
RegKey=Software\Microsoft\Windows\CurrentVersion\Explorer\VirtualDesktops
RegValue=VirtualDesktopIDs
OnUpdateAction=[!SetVariable Temp_Desktop_Count "[&Measure_Script:GetDesktopCount()]"][!WriteKeyValue Variables Desktop_Count "[#Temp_Desktop_Count]"][!SetVariable Desktop_Count "[#Temp_Desktop_Count]"][!UpdateMeter *][!Redraw][!SetOption Measure_Desktop_Count OnUpdateAction ""]
OnChangeAction=[!SetVariable Temp_Desktop_Count "[&Measure_Script:GetDesktopCount()]"][!WriteKeyValue Variables Desktop_Count "[#Temp_Desktop_Count]"][!SetVariable Desktop_Count "[#Temp_Desktop_Count]"][!UpdateMeter *][!Redraw]
RegExpSubstitute=1
Group=VirtualDesktopMeasures
Substitute="(.{32})":"\1 "

;----------------------------------------------------------------------
; Measures for <LinkToCurrentDesktop>

; This measure is needed to know what script use.
[MeasureOSVersion]
Measure=Plugin
Plugin=SysInfo
SysInfoType=OS_VERSION
RegExpSubstitute=1
Substitute=".*Windows 10.*":"1",".*Windows 11.*":"0"

; This measure is needed for Windows 10, no longer required for Windows 11.
[Measure_Current_Session]
Measure=Registry
RegHKey=HKEY_CURRENT_USER 
RegKey=Software\Microsoft\Windows\CurrentVersion\Explorer\SessionInfo
OutputType=SubKeyList
UpdateDivider=-1

[Measure_Current_Desktop]
Measure=Registry
RegHKey=HKEY_CURRENT_USER
RegKey=[#Registry_RegKey_Current_[&MeasureOSVersion]]
RegValue=CurrentVirtualDesktop
Group=VirtualDesktopMeasures
OnUpdateAction=[!SetVariable Temp_Current_Desktop "[&Measure_Script:GetCurrentDesktop()]"][!WriteKeyValue Variables Current_Desktop "[#Temp_Current_Desktop]"][!SetVariable Current_Desktop "[#Temp_Current_Desktop]"][!UpdateMeter *][!Redraw][!SetOption Measure_Current_Desktop OnUpdateAction ""]
OnChangeAction=[!SetVariable Temp_Current_Desktop "[&Measure_Script:GetCurrentDesktop()]"][!WriteKeyValue Variables Current_Desktop "[#Temp_Current_Desktop]"][!SetVariable Current_Desktop "[#Temp_Current_Desktop]"][!UpdateMeter *][!Redraw]
