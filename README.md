# DZTimer
Some timers for Windows. / Windows平台下的各种定时器。

## 介绍
DZTimer, 利用Windows平台下的相关API，封装了相关的定时器类。<br/>
具体包括：
#
|类名|Windows API|定时器精度|  
|:---|:---|:---|
|CEventTimer|timeSetEvent()|毫秒级|
|CQueueTimer|CreateTimerQueueTimer()|毫秒级| 
## 精度分析
* timeSetEvent()  
经测试，此接口精度很高，误差基本在0.1ms内。
* CreateTimerQueueTimer()  
经测试，此接口精度较高，受系统方面影响较多，误差少时0.2ms左右，多时可达9ms左右。
## 注意
* timeSetEvent()
在单个进程内，最多同时启用`16`个此类型的定时器。



