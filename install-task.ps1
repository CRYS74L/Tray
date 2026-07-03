$ErrorActionPreference = 'Stop'

$root = Split-Path -Parent $MyInvocation.MyCommand.Path
$taskName = 'Lyrics Tray Icon Fix'
$launcher = Join-Path $root 'run-hidden.vbs'
$wscript = Join-Path $env:WINDIR 'System32\wscript.exe'
$runKey = 'HKCU:\Software\Microsoft\Windows\CurrentVersion\Run'
$value = '"' + $wscript + '" "' + $launcher + '"'

New-Item -Path $runKey -Force | Out-Null
Set-ItemProperty -Path $runKey -Name $taskName -Value $value -Type String
Write-Host "已创建当前用户登录启动项: $taskName"
