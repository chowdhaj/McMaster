Dim oShortCutLink,DesktopPath, WshShell, CurDir, ltsajar
set WshShell = WScript.CreateObject("WScript.Shell")
DesktopPath = WshShell.SpecialFolders("Desktop")
CurDir = WshShell.CurrentDirectory
set oShortCutLink = WshShell.CreateShortcut(DesktopPath & "\ltsa V3.0.lnk")
oShortCutLink.TargetPath = "C:\WINDOWS\system32\javaw.exe"
ltsajar = """" & CurDir & "\ltsa.jar" & """" 
oShortCutLink.Arguments = "-Xmx512m -jar " &  ltsajar 
oShortCutLink.WorkingDirectory = CurDir
oShortCutLink.IconLocation = CurDir & "\ltsa.ico"
oShortCutLink.WindowStyle = 1
oShortCutLink.Description = "Ltsa V3.0 Shortcut"
oShortCutLink.Save