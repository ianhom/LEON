# 一种802.15.4 CSMA-CA算法实现 
- ZigBee和6loWPAN都可使用802.15.4的MAC+PHY，802.15.4为了让节点更好地接入信道（channel），MAC层中使用了CSMA-CA机制。根据采用信标网络还是非信标网络，分别使用时隙CSMA-CA（适合星状网和树状网）和非时隙CSMA-CA(适合网状网)。
该实现方法尝试了非时隙CSMA-CA算法实现，时隙CSMA-CA将在日后进行补充。

## 使用方法：
1. 初始化数据结构：
     * tCsmaData.ucSlotted          = CSMA_CA_WITHOUT_SLOTTED;  /* 非时隙 */
     * tCsmaData.ucBatteryExtension = BATTERY_EXTENSION_DIS;    /* 不启用电池寿命扩展 */
     * tCsmaData.pfCCA              = CCA;                      /* 空闲信道评估函数（随机数模拟） */
     * tCsmaData.pfRandom           = Random;                   /*  随机数函数（ADC模拟） */
2. 初始化CSMA-CA   CSMA_CA_Init(&tCsmaData);
3. 使用CSMA-CA      ucReturn = CSMA_CA();
4. 根据CSMA-CA 返回结果进行报文发送。
