# 简介  

![image](DocumentPictures/Product/G_Title.png)  

&emsp;&emsp;XGLoginClient is an Unreal Engine 5 plugin, which supports you to access XGLoginServer in the Unreal project, and can achieve user registration, login, consumption, recharge, query and other operations.It is developed based on UE5's built-in Http module and contains only client code.</br>
&emsp;&emsp;XGLoginServer is an Unreal Engine 5 standalone program that is compiled on the Unreal Engine version 5.0.3 source code and can respond to users' network requests.It is based on the UE5 built-in HttpServer module for development, and the use of related database plugin can access the database MySQL-5.7.26 version. </br>
&emsp;&emsp;The XGLoginServer programs, database plug-ins, database software, etc. required by the server are not distributed here.  
&emsp;&emsp;If necessary, please contact the relevant service provider or the author of this plugin.  
&emsp;&emsp;Depending on your usage, you may need a network environment that has access to the public IP address where XGLoginSever resides.  
&emsp;&emsp;Plugin URL:  
&emsp;&emsp;&emsp;&emsp;[XGLoginClient(Wait for upload, currently unavailable)]();  
&emsp;&emsp;Sample Project URL:  
&emsp;&emsp;&emsp;&emsp;[XGLogClientDemo(Wait for upload, currently unavailable)]();  
&emsp;&emsp;English Description:  
&emsp;&emsp;&emsp;&emsp;[README](./README.md)  
&emsp;&emsp;Chinese Description:  
&emsp;&emsp;&emsp;&emsp;[中文说明书](./README_CN.md)  

Attention:  
1.The XGLoginClient plugin uses only the code provided by Unreal Engine 5 and has no other dependencies;  
2.All data of XGLoginClient Plugin is test data,do not use real information, and test data will be cleaned regularly;  
3.The XGLoginClient plugin does not contain server-side content;  
4.The XGLoginServer is not guaranteed to be available in real time.
# XGLoginClient  
## Blueprints  

![image](DocumentPictures/Product/G_AllCode.png)  

## Flows

&emsp;&emsp;a.Configure access parameters</br>
&emsp;&emsp;b.Make an access request</br>
&emsp;&emsp;c.Process the returned result</br>

## Access parameters

![image](DocumentPictures/Product/G_XGLoginClientSettings.png)  

## 访问请求
### Simple Check
&emsp;&emsp;Simple verification</br>
&emsp;&emsp;Verify that the client plugin and server are token-matched and version-matched.</br>

![image](DocumentPictures/Product/G_Code_SimepleCheck.png)  

### Simple Login

&emsp;&emsp;Simple entry</br>
&emsp;&emsp;Enter your account and password to log in</br>

![image](DocumentPictures/Product/G_Code_SimpleLogin.png)  

### Simple Register

&emsp;&emsp;Simple registration</br>
&emsp;&emsp;Enter your account, password, phone number and email address.</br>
&emsp;&emsp;The account and password are 6 to 18 digits and letters, the phone number is a pure 11 number, and the email must contain the @ sign. Cannot contain any illegal characters</br>

![image](DocumentPictures/Product/G_Code_SimpleRegister.png)  

### Simple Charge

&emsp;&emsp;Simple top-up</br>
&emsp;&emsp;Enter the administrator account and password, and the account and amount to be topped up.</br>

![image](DocumentPictures/Product/G_Code_SimpleCharge.png)  

### Simple Consume

&emsp;&emsp;Simple consumption</br>
&emsp;&emsp;Enter the account to be spent, password, amount spent</br>

![image](DocumentPictures/Product/G_Code_SimpleConsume.png)  

### Simple Query

&emsp;&emsp;Simple query</br>
&emsp;&emsp;Enter your account, password, and get your account balance</br>

![image](DocumentPictures/Product/G_Code_SimpleQuery.png)  

### LoginWithMachineID

&emsp;&emsp;Sign in with machine code</br>
&emsp;&emsp;Enter your account, password and machine code word to log in</br>
&emsp;&emsp;If the custom machine code needs to be entered, the local machine code will be read if the custom machine code is not defined</br>
&emsp;&emsp;The machine code is 1 to 32 bits of numbers and letters.</br>

![image](DocumentPictures/Product/G_Code_Machine_Login.png)  

### RegisterWithMachineID

&emsp;&emsp;Register with machine code</br>
&emsp;&emsp;Enter account, password, mobile number, email, machine code</br>
&emsp;&emsp;The account and password are 6 to 18 digits and letters, the phone number is a pure 11 number, and the email must contain the @ sign. Cannot contain any illegal characters.</br>
&emsp;&emsp;If the custom machine code needs to be entered, the local machine code will be read if the custom machine code is not defined</br>
&emsp;&emsp;The machine code is 1 to 32 bits of numbers and letters.</br>

![image](DocumentPictures/Product/G_Code_Machine_Register.png)  

### GetRemoteMachineIDAndRegisterTIme

&emsp;&emsp;Get the initial registration machine code and initial registration time for this account.</br>
&emsp;&emsp;Enter your account, password.</br>

![image](DocumentPictures/Product/G_Code_Machine_GetRemoteInfo.png)  

### GetLocalMachineID

&emsp;&emsp;Gets the native machine code</br>

## Sample Project  

![image](DocumentPictures/Product/G_DemoShow.png)  

# XGLoginServer  
&emsp;&emsp;Server documentation, code, compiled programs are not distributed here.  
&emsp;&emsp;Testing the Public IP Addresses:[47.108.203.10]  
&emsp;&emsp;Testing the public network port:[8036]  
&emsp;&emsp;Testing the access token:[XG]  
&emsp;&emsp;Testing the access token encryption times :[10]  
&emsp;&emsp;Testing the administrator account:[XiaoGang]  
&emsp;&emsp;Testing the administrator password:[123456]  

## Contact Information    

Please contact me if you have any questions about [XGLoginClient(Wait for upload, currently unavailable)]().

QQ:
709777172  

Email:
709777172@qq.com  

bilibili:
[虚幻小刚](https://space.bilibili.com/8383085)  
