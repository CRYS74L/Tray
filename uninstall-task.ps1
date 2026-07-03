$ErrorActionPreference = 'SilentlyContinue'

$taskName = 'Lyrics Tray Icon Fix'
$runKey = 'HKCU:\Software\Microsoft\Windows\CurrentVersion\Run'
Remove-ItemProperty -Path $runKey -Name $taskName -Force
Write-Host "已删除当前用户登录启动项: $taskName"
