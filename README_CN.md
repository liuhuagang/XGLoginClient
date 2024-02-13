# 简介  

![image](DocumentPictures/Product/G_Title.png)  

&emsp;&emsp;XGLoginClient是一款虚幻引擎5插件,它支持你在虚幻项目中访问XGLoginServer,可以实现对用户的注册、登录、消费、充值、查询等操作.它是基于UE5内置的Http进行开发的,只包含客户端代码.  
&emsp;&emsp;XGLoginServer是一款虚幻引擎5独立程序,在虚幻引擎版本5.0.3的源码上进行编译,可以实现对用户的网络请求响应.它是基于UE5内置的HttpServer进行开发,并使用了相关数据库插件可以访问数据库MySQL-5.7.26版本.  
&emsp;&emsp;服务端所需要的XGLoginServer程序、数据库插件、数据库软件等不会通过此处进行分发.  
&emsp;&emsp;如果有需要请联系相关服务商或本插件作者.  
&emsp;&emsp;根据你的使用情况,你可能需要可以访问XGLoginSever所在公网IP的网络环境.  
&emsp;&emsp;虚幻商城插件地址:  
&emsp;&emsp;&emsp;&emsp;[XGLoginClient(等待通过后上传,目前不可用)]();  
&emsp;&emsp;示例项目下载:  
&emsp;&emsp;&emsp;&emsp;[XGLogClientDemo(等待通过后上传,目前不可用)]();  
&emsp;&emsp;英文说明:  
&emsp;&emsp;&emsp;&emsp;[README](./README.md)  
&emsp;&emsp;中文说明:  
&emsp;&emsp;&emsp;&emsp;[中文说明书](./README_CN.md)  

注意:  
1.XGLoginClient插件仅使用了虚幻引擎5提供的代码,不含其他依赖;  
2.XGLoginClient插件所有数据均为测试数据,请勿使用真实信息,测试数据会被定期清理;  
3.XGLoginClient插件不包含服务端的内容;  
# XGLoginClient  
## 蓝图速览  

![image](DocumentPictures/Product/G_AllCode.png)  

## 使用流程

&emsp;&emsp;a.配置访问参数</br>
&emsp;&emsp;b.发出访问请求</br>
&emsp;&emsp;c.处理返回结果</br>

## 访问参数

![image](DocumentPictures/Product/G_XGLoginClientSettings.png)  

## 访问请求
### Simple Check
&emsp;&emsp;简单验证</br>
&emsp;&emsp;验证客户端插件与服务器是否令牌匹配和版本匹配

![image](DocumentPictures/Product/G_Code_SimepleCheck.png)  

### Simple Login

&emsp;&emsp;简单登录</br>
&emsp;&emsp;输入账户和密码进行登录

![image](DocumentPictures/Product/G_Code_SimpleLogin.png)  

### Simple Register

&emsp;&emsp;简单注册</br>
&emsp;&emsp;输入账户,密码,手机号和邮箱.</br>
&emsp;&emsp;账户和密码是6到18位数字和字母,手机号为纯11数字,邮箱必须包含@符号.不能包含任何非法字符.</br>

![image](DocumentPictures/Product/G_Code_SimpleRegister.png)  

### Simple Charge

&emsp;&emsp;简单充值</br>
&emsp;&emsp;输入管理员账户及密码,待充值账户及金额.</br>

![image](DocumentPictures/Product/G_Code_SimpleCharge.png)  

### Simple Consume

&emsp;&emsp;简单消费</br>
&emsp;&emsp;输入待消费账户,密码,消费金额</br>

![image](DocumentPictures/Product/G_Code_SimpleConsume.png)  

### Simple Query

&emsp;&emsp;简单查询</br>
&emsp;&emsp;输入账户,密码,获取账户余额</br>

![image](DocumentPictures/Product/G_Code_SimpleQuery.png)  

### LoginWithMachineID

&emsp;&emsp;携带机器码登录</br>
&emsp;&emsp;输入账户,密码和机器码字进行登录</br>
&emsp;&emsp;如果自定义机器码需要输入自定义的机器码,未自定义会读取本机机器码.</br>
&emsp;&emsp;机器码为1到32位的数字和字母.</br>

![image](DocumentPictures/Product/G_Code_Machine_Login.png)  

### RegisterWithMachineID

&emsp;&emsp;携带机器码注册</br>
&emsp;&emsp;输入账户,密码,手机号,邮箱,机器码</br>
&emsp;&emsp;账户和密码是6到18位数字和字母,手机号为纯11数字,邮箱必须包含@符号.不能包含任何非法字符.</br>
&emsp;&emsp;如果自定义机器码需要输入自定义的机器码,未自定义会读取本机机器码.</br>
&emsp;&emsp;机器码为1到32位的数字和字母.</br>

![image](DocumentPictures/Product/G_Code_Machine_Register.png)  

### GetRemoteMachineIDAndRegisterTIme

&emsp;&emsp;获取本账户的初始注册机器码和初始注册时间</br>
&emsp;&emsp;输入账户,密码</br>

![image](DocumentPictures/Product/G_Code_Machine_GetRemoteInfo.png)  

### GetLocalMachineID
&emsp;&emsp;获取本机机器码</br>

## 示例项目  

![image](DocumentPictures/Product/G_DemoShow.png)  

# XGLoginServer  
&emsp;&emsp;服务器文档,代码,编译后的程序不在此处分发.  
&emsp;&emsp;测试公网IP:[47.108.203.10]  
&emsp;&emsp;测试公网端口:[8036]  
&emsp;&emsp;测试访问令牌:[XG]  
&emsp;&emsp;测试访问令牌加密次数:[10]  
&emsp;&emsp;测试管理员账户:[XiaoGang]  
&emsp;&emsp;测试管理员密码:[123456]
# 联系方式  

如果有任何[XGLoginClient(等待通过后上传,目前不可用)]()插件产品问题,请联系我.  

QQ:
709777172  

Email:
709777172@qq.com  

bilibili:
[虚幻小刚](https://space.bilibili.com/8383085)  