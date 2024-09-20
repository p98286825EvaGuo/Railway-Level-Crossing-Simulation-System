Railway Level Crossing Simulation System  
平交道模擬系統
===

> Final project for Microprocessor Principles And Applications class in NCKU CSIE  
> Project Developing Time: Dec 2023 – Jan 2024  
> **If you want to reference more about our project, just see our demo video!**

### Demo Video
[link](https://youtu.be/4mxQOoanrgY)

### 組別資訊
* Team Number: Group 1
* Team Members: 陳帛愛, 郭沛蓉, 黃友枚, 孫以瑭

### 專題動機
組員在搭火車回家路上討論專題主題，靈機一動提出可以做平交道模擬系統，  
經組員們討論後，發現課堂上學過的知識都可以應用在這個系統上，所以決定實作此系統作為期末專題內容。

### 原始設計草稿
![24068](https://github.com/Esther2002-soon/FinalProject_Microprocessor/assets/106828044/b74f8e01-6957-4345-84b4-dd2ebf67c782)

### 系統功能與原理說明
- 系統功能
    - 模擬平交道系統，火車經過時護欄關閉，火車離開後護欄打開
    - 系統共分為 3 種狀態
        - 紅綠燈狀態: 無火車經過，護欄維持開啟，紅綠燈進行倒數
        - 火車經過狀態: 護欄放下、警示燈閃爍、紅綠燈顯示紅燈，等待火車經過
        - 緊急狀態: 護欄放下、警示燈恆亮、紅綠燈顯示紅燈
- 原理說明
    - 利用伺服馬達作為護欄
    - 利用紅外線障蔽傳感器，偵測火車是否已經離開
    - 利用七段顯示器顯示紅綠燈倒數秒數
    - 利用 LED 燈做為紅綠燈
    - 利用 button 輸入火車來臨訊號
    - 利用 button 輸入緊急狀態訊號
    - 利用 UART 顯示平交道系統狀態

### 系統使用環境及對象
- 系統使用環境: MPLAB v5.20
- 語言: C
- 編譯器: XC8 v2.40
- 燒錄器: pickit4
- 晶片: PIC18F4520

### 系統完整架構圖
<img width="725" alt="Screenshot 2024-01-07 at 1 51 54 AM" src="https://github.com/Esther2002-soon/FinalProject_Microprocessor/assets/106828044/388dcf71-c4e6-4918-8b2a-e97ed51d99f7">

### 系統狀態圖
<img width="812" alt="Screenshot 2024-01-07 at 2 11 47 AM" src="https://github.com/Esther2002-soon/FinalProject_Microprocessor/assets/106828044/5b9c9370-7a23-4e0c-baf5-8d29534068a1">

### 電路圖
  
![S__2891801](https://github.com/Esther2002-soon/FinalProject_Microprocessor/assets/106828044/3e8bf7a8-7c11-4b16-81aa-62dcb7e3c41a)

- 設計
    1. 通知火車即將抵達：按按鈕後倒數 5 秒，5 秒後火車經過
    2. 模擬平交道的安全護欄放下：利用伺服馬達控制
    3. 警示燈於欄杆放下期間閃爍，放下後恆亮燈：利用 LED 燈控制
    4. 感測火車，待火車通過後護欄升起：利用紅外線及超音波感測器
    5. 紅綠燈：利用 timer 的設定切換，並透過七段顯示器顯示紅綠燈秒數
    6. 緊急按鈕：利用 interrupt 放下護欄並亮起特殊燈況告知

### 系統開發工具、材料及技術
- 開發工具、材料
    - PIC18F4520
    - PICKIT 4
    - 紅外線障蔽傳感器 MH-B
    - 七段顯示器 C-583Q-12 BVN-7572SR4
    - button
    - LED
    - server motor
    - UART

- 系統開發技術
    - 單元項目
        - interrupt (button, infrared ray)
        - timer (timer2 for CCP module)
        - UART (show state)
        - ADC (server motor)
        - PWM (server motor)
    - 進階項目 
        - 紅外線障蔽傳感器
        - 七段顯示器
- 系統開發技術各項詳述
    - timer (timer2 for CCP module)
    - UART (show state)
        - 利用 UART 生成字串警示
        - Train mode : 開始生成 "start" 結束生成 "stop"
        - emergency mode : 開始生成 "emergency" 結束生成 "emergency off"
    - PWM (server motor)
        - 利用 PWM mode 產生方波，控制伺服馬達轉的角度(-90 度 ～ 0 度)
    - 紅外線障蔽傳感器
        - 總共有三個接頭左至右為OUTPUT GND VCC  
        
          <img width="400" alt="Screenshot 2024-01-10 at 3 24 44 PM" src="https://github.com/Esther2002-soon/FinalProject_Microprocessor/assets/106828044/6ba3669a-8b65-419c-9294-51858bfa7811">

        - OUT 接到 RB1，0 為感測到物體
    - 七段顯示器 
        - 紅綠燈之倒數

### 實際組員之分工項目
- 陳帛愛：UART、button、傳感器整合、整合系統、測試、製作道具、report 製作
- 郭沛蓉：UUART、button、傳感器整合、整合系統、測試、製作道具、report 製作
- 黃友枚：紅外線傳感器、button、傳感器整合、整合系統、測試、製作道具、report 製作
- 孫以瑭：七段顯示器計時、紅綠燈、report 製作整合、測試、製作道具
  
### 遇到的困難及如何解決
- 困難：多個晶片無法整合溝通
    - 解決方法：將所有晶片的功能整合到一個晶片上
- 困難: 原本打算使用七段顯示器倒數二位數秒數，但是把功能整合到一個晶片上後導致port不夠
    - 解決方法：改成一位數時間倒數
- 困難: 七段顯示器2.3digit的pin腳資料由於各個型號各異，沒有統一資料
    - 解決方法：一根一根pin腳測試
- 困難: 紅外線傳感器故障，無條件感測到物品
    - 解決方法：再買一個嗚嗚
- 困難：實驗課發放的按鈕在本專題無法使用（但問題並不是按鈕本身壞掉，目前尚未知為何按鈕按下會導致程式中斷）
    - 解決方法：經測試發現使用別款按鈕程式可正常執行，因此改放棄原按鈕
