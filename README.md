
# Genshin Impact FPS Unlocker
 - This tool helps you to unlock the 60 fps limit in the game
 - This is an external program uses **WriteProcessMemory** to write the desired fps to  the game
 - Handle protection bypass is already included
 - Does not require a driver for R/W access
 - Supports OS and CN version
 - Should works for future updates
 - If the source needs to be updated, I'll try to do it as soon as possible
 - You can download the compiled binary over at '[Release](https://github.com/34736384/genshin-fps-unlock/releases)' if you don't want to compile it yourself
 ## Compiling
 - Use  Visual Studio 2019 Community Edition to compile
 - Not required but I know it works on this version
 ## Usage
 - Make sure you have the [Visual C++ 2019 Redistributable (x64)](https://aka.ms/vs/16/release/vc_redist.x64.exe) and [.NET Framework 4.8](https://dotnet.microsoft.com/en-us/download/dotnet-framework/net48) installed
 - If it is your first time running, unlocker will attemp to find your game through registry. If it failes then it will ask you to either browse or run the game.
 - Place the compiled exe anywhere you want
 - Make sure your game is closed, the unlocker will automatically start the game for you
 - Run the exe as administrator, and leave the exe running
 >It requires adminstrator because the game needs to be started by the unlocker and the game requires such permission
 - To inject other third party plugins (e.g. reshade), go to `Options->Settings->DLLs` and click add

## Version 2.0.0 Changes
 - Removed key binds
 - Added a GUI (should removed the need for keybinds)
 - Added interactable lauch option configurations (Located under `Options->Settings->Lauch Options`) 
 - Added some QoL features, such as start minimized, minimize to tray, game process priority, and power saving
 - **Minimize to tray**: Whenever you click minimize or have the `Start Minimized` option checked, the unlocker will automatically minimize to tray
 - **Game Process Priority**: Changes the process priority on start, and it will be saved in config too!
 - **Power Saving**: Automatically sets the fps limit to 10 and low process priority upon losing focus to the game (e.g. tabbing out of game)
 - Added a slider and an input box for changing fps cap
 - Added an icon
 - Added game path detection through registry, will fallback to old method if it fails with registry
 - You can choose different installation of the game in `Options->Setup`
 ## Notes
 - My test account is currently AR55, can't guaranteed it will be safe forever, But honestly though, I doubt they would ban you for this.
 - Modifying game memory with an unauthorized third party application is a violation of the ToS, so use it at your own risk (same thing applies for injecting reshade)
 ## Todo
 - idk maybe add localization or game predownload


# 原神解锁FPS限制

 - 工作原理类似于外部辅助，通过**WriteProcessMemory**把FPS数值写进游戏
 - 不需要通过驱动进行读写操作
 - 支持国服和外服
 - 理论上支持后续版本，不需要更新源码
 - 如果需要更新我会尽快更新

## 食用指南
 - 运行前确保系统已安装[Visual C++ 2019 Redistributable (x64)](https://aka.ms/vs/16/release/vc_redist.x64.exe)和[.NET Framework 4.8](https://dotnet.microsoft.com/en-us/download/dotnet-framework/net48)
 - 第一次运行的话先以管理员运行，解锁器会尝试通过注册表寻找游戏路经，如果找不到的话会提示你浏览游戏位置或者开启游戏
 - 解锁器放哪都行
 - 运行之前确保游戏是关闭的
 - 用管理员运行解锁器
 - 解锁器不能关掉
>使用管理员运行是因为游戏必须由解锁器启动，游戏本身就需要管理员权限了，所以负责启动的也是需要的


## 注意
- 使用未认证的第三方软件修改游戏数据是违反了协议条款的，后果自负
- 转载随便，可以的话就注明下出处
- 请不要倒卖
## 中文化完成
## 添加多账户管理功能
![image](https://user-images.githubusercontent.com/103351906/230716822-a780fa89-343e-429c-95b0-36e9329e057f.png)
![image](https://user-images.githubusercontent.com/103351906/230716837-31a8305e-aab7-485a-8064-c5fed5f77e51.png)
![image](https://user-images.githubusercontent.com/103351906/230716847-09e09462-1571-4cf2-b102-a14bf9d00654.png)
