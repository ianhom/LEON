# 关于W5500
## 概述
- 硬件TCP/IP协议栈，包含MAC+PHY
- 支持TCP,UDP,IPv4，ICMP,ARP，IGMP和PPPoE
- 32k ram收发缓存报文，发送/接收各16k
- 8个硬件socket独立通讯
- SPI接口，最高80MHz
- 10/100M速率

## SPI数据帧格式
- W5500包含：    
    1. 2字节的地址段；
    2. 1字节的控制段；
    3. N字节的数据段；

### 地址段
地址段为“W5500寄存器”，“发送缓存”和“接收缓存”的16位偏移。

### 控制段
- 1字节控制段中的BIT3-BIT7的Block Select Bits用于选择**区域**。    
- W5500有如下区域：
    - 通用寄存器区
    - Socket X寄存器区
    - Socket X 发送缓存区
    - Socket X 接收缓存区    
- 解析方式如下：
    - 00000b = 通用寄存器区    
    - XXX01b  = Socket X寄存器区（X = 0~7）
    - XXX10b  = Socket X发送缓存区（X = 0~7）
    - XXX11b  = Socket X接受缓存区（X = 0~7）
    - XXX00b  = 保留未使用（X = 0~7）**选择该区域将会导致W5500故障**。

- 1字节控制段中的BIT2为读写设置位：
    - 0 = 读
    - 1 = 写

- 1字节控制段中的BIT0-BIT1为操作模式位：
    - 00 = 可变长度模式（**由SCSn控制报文的启停**）
    - 01 = 固定长度模式，1字节长度
    - 10 = 固定长度模式，2字节长度
    - 11 = 固定长度模式，4字节长度

### 数据段
- 无特别说明。    

## 寄存器和缓存
### 通用寄存器区
- 通用寄存器包含了W5500的基本信息。地址范围为0x0000到0x0039，包括如下信息可配置：
    1. 模式
    2. 网关地址
    3. 子网掩码
    4. 硬件源地址（MAC）
    5. IP地址
    6. 中断低等级定时器
    7. 中断
    8. 中断掩码
    9. socket中断
    10. socket中断掩码
    11. 重发时间
    12. PPP LCP 请求定制器
    13. PPP LCP Magic数
    14. PPP目标MAC地址
    15. PPP会话指示
    16. PPP最大段SIZE
    17. unreachable IP地址
    18. unreachable 端口
    19. PHY配置
    20. 芯片版本
    
### socket寄存器区
- socket基本配置信息：
    1. socket模式
    2. socket命令
    3. socket中断
    4. socket状态
    5. socket源端口
    6. socket目标MAC
    7. socket目标IP地址
    8. socket目标端口
    9. socket最大段size
    10. socket IP TOS
    11. socket IP TTL
    12. socket接收buffer大小
    13. socket发送buffer大小
    14. socket发送buffer空闲大小
    15. socket发送buffer读指针
    16. socket发送buffer写指针
    17. socket接收buffer已存size
    18. socket接收buffer读指针
    19. socket接收buffer写指针
    20. socket中断掩码
    21. socket IP头部中的Fragment偏移
    22. Keep alive定时器
    
### 收发缓存
- W5500的收发缓存各16k，初始时，每个socket的收和发的缓存各2k，可通过socket寄存器重新分配。    

## 寄存器详述
### 通用寄存器
- MR 模式寄存器：
    - bit7         Rest   复位，为1时复位，上电自动为0
    - bit5         WOL    网络唤醒功能，0 = 关闭；1 = 打开
    - bit4         PB     禁止PING功能，0 = 不禁止；1 = 禁止，不回应PING请求
    - bit3         PPPoE  PPPoE模式，   0 = 关闭；1 = 打开
    - bit1         FARP   强制ARP模式   0 = 关闭；1 = 打开

- GAR 网关IP地址寄存器

- SUBR 子网掩码寄存器

- SHAR 源MAC地址

- SIPR 源IP地址

- INTLEVEL 低电平中断定时器寄存器：
    - 设置中断生效等待时间，在下一个中断触发后，中断引脚INTn将在INTLEVEL时间后拉低。

- IR 中断寄存器：
    - 指明中断的状态，为0时INTn管脚拉高，反之拉低。

- IMR 中断屏蔽寄存器
    - 屏蔽对应中断

- SIR socket中断寄存器
    - 指明socket中断状态

- SIMR socket中断屏蔽寄存器

- RTR 重试时间寄存器
    - 配置重传时间值

- RCR 重试计数寄存器
    - 配置重试次数
    
- PTMER PPP连接控制协议请求定时器寄存器

- PMAGIC PPP连接控制协议幻数寄存器

- PHAR PPPoE模式下模板MAC地址寄存器

- PSID PPPoE模式下会话ID寄存器

- PMRU PPPoE模式下最大接收端元

- UIPR 无法抵达IP地址寄存器

- PHYCFGR PHY配置寄存器
    - 配置PHY工作模式及PHY重启，并指明PHY状态

- VERSIONR 版本寄存器
