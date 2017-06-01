//
//  Manager.h
//  PayTest
//
//  Created by 张炯 on 17/5/12.
//  Copyright © 2017年 张炯. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef void(^SAPayManagerResponseBlock)(NSInteger responseCode, NSString *responseMsg);

@interface SAPlatformPayManager : NSObject


/*
 responseCode:
 0    -    支付成功
 -1   -    支付失败
 -2   -    支付取消
 -3   -    未安装App(适用于微信)
 -4   -    设备或系统不支持，或者用户未绑卡(适用于ApplePay)
 -99  -    未知错误
 */



/**
 
 重要说明
 privateKey等数据严禁放在客户端，加签过程务必要放在服务端完成；
 防止商户私密数据泄露，造成不必要的资金损失，及面临各种安全风险；
 
 */



/**
 实例化一个支付管理对象

 @return 支付管理对象
 */
+ (SAPlatformPayManager *)sharePayManager;





//***************支付宝*****************//

/*
 支付宝支付结果回调
 */
@property (nonatomic, strong)SAPayManagerResponseBlock alipayResponseBlock;

/*
 处理支付宝通过URL启动App时传递回来的数据 AppDelegate
 */
+ (BOOL)alipayHandleOpenURL:(NSURL *)url;

/*
 发起支付宝支付
 */
- (void)aliPayOrder:(NSString *)order
             scheme:(NSString *)scheme
          responseBlock:(SAPayManagerResponseBlock)block;




//***************微信*******************//

@property (nonatomic, strong)SAPayManagerResponseBlock WXPayResponseBlock;

/**
 注册微信支付

 @param appId 微信开放平台应用appid
 @param description 描述
 @return 是否注册成功
 */
+ (BOOL)WXPayRegisterAppWithAppId:(NSString *)appId description:(NSString *)description;


/*
 处理微信通过URL启动App时传递回来的数据 AppDelegate
 */
+ (BOOL)WXPayHandleOpenURL:(NSURL *)url;


/**
 发起微信支付

 @param appId 微信开放平台审核通过的应用APPID
 @param partnerId 微信支付分配的商户号
 @param prepayId 微信生成的预支付回话标识，该值有效期为2小时
 @param package 暂填写固定值Sign=WXPay
 @param nonceStr 随机字符串，不长于32位。推荐随机数生成算法
 @param timeStamp 时间戳，请见接口规则-参数规定
 @param sign 签名，详见签名生成算法
 @param block 支付结果回调
 */
- (void)WXPayWithAppId:(NSString *)appId partnerId:(NSString *)partnerId prepayId:(NSString *)prepayId package:(NSString *)package nonceStr:(NSString *)nonceStr timeStamp:(NSString *)timeStamp sign:(NSString *)sign respBlock:(SAPayManagerResponseBlock)block;




//***************银联*****************//

/*
 银联支付结果回调
 */
@property (nonatomic, strong)SAPayManagerResponseBlock UPPayResponseBlock;

/*
 处理银联通过URL启动App时传递回来的数据
 */
- (BOOL)UPPayHandleOpenURL:(NSURL*)url;



/**
 发起银联支付

 @param serialNo 是交易流水号
 @param viewController 发起支付的控制器
 @param block 支付结果回调
 */
- (void)UPPayWithSerialNo:(NSString *)serialNo
               fromScheme:(NSString *)scheme
              viewController:(id)viewController
                   responseBlock:(SAPayManagerResponseBlock)block;



//***************Apple Pay*****************//







+ (BOOL)handlePayOpenUrl:(NSURL *)url;


@end
