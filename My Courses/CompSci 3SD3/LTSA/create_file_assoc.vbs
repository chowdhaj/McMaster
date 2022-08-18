Dim EXT, Filetype, FileName, b, CurDir, IconFile, ltsajar
Set b = CreateObject("wscript.shell")
CurDir = b.CurrentDirectory
EXT = ".lts"
FileType = "ltsfile"
ltsajar = """" & CurDir & "\ltsa.jar" & """" 
Application = "C:\WINDOWS\system32\javaw.exe -Xmx512m -jar " & ltsajar  
IconFile = CurDir & "\ltsafile.ico"
b.regwrite "HKCR\" & EXT & "\", FileType
b.regwrite "HKCR\" & FileType & "\", "LTS model description in FSP"
b.regwrite "HKCR\" & FileType & "\DefaultIcon\", IconFile 
b.regwrite "HKCR\" & FileType & "\shell\open\command\", Application & " ""%1"""
