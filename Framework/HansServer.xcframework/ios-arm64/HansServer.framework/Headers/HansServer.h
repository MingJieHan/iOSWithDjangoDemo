//
//  HansServer.h
//  HansServer
//
//  Created by jia yu on 2021/7/19.
//

#import <Foundation/Foundation.h>
#import <HansServer/HansServerHandler.h>
#import <HansServer/HansRequestManager.h>
#import <HansServer/HansCache.h>
#import <HansServer/HansServerUserObject.h>
#import <HansServer/HansSignUpViewController.h>
#import <HansServer/HansForgotPasswordViewController.h>
#import <HansServer/HansLoginViewController.h>
#import <HansServer/HansAccountDetailTableViewController.h>
#import <HansServer/HansServerHtmlResultObject.h>
#import <HansServer/NSDjangoUTCConvert.h>

//about Edit
#import <HansServer/HansLineStringEditViewController.h>
#import <HansServer/HansManyLineStringEditViewController.h>
#import <HansServer/HansInputFloatViewController.h>
#import <HansServer/HansSelectOneTableViewController.h>
#import <HansServer/HansInformationViewController.h>

extern float HansServerVersion;         //1.1 etc
extern NSInteger HansServerBuildNumber; //3453 etc

#define Current_User_Changed_Notification_Name @"Current_User_Changed_Notification_Name"
#define HANS_SERVER_ERROR_KEY @"error"

extern NSBundle * _Nonnull HansServerBundle;
//NSLocalizedStringFromTableInBundle(@"Loading...", @"HansServer", HansServerBundle, nil);

NS_ASSUME_NONNULL_BEGIN
@interface HansServer : NSObject
@property (nonatomic) NSString *server;         //ip.ip.ip.ip or www.domain.com
@property (nonatomic) NSInteger port;           //default is 80
@property (nonatomic) BOOL requestHttps;        //default is NO
@property (nonatomic) BOOL isDevelopmentToken;  //default is NO
@property (nonatomic) NSString *bundleIdentifierForToken;   //
@property (nonatomic) NSString *userAgent;      //default is @"Hans WebKit"
@property (nonatomic) NSString *verifyAppendKey;    //服务器通讯校验计算额外Key， default is Hans

//HansServer sent notification while currentUser changed.
@property (nonatomic) HansServerUserObject * _Nullable currentUser;

+(HansServer *)shareServer;

-(void)thisDeviceNotificationToken:(NSData *)token;

-(NSString *)buildURL:(NSString *)urlPath;

-(void)request:(NSString *)urlpath withHandler:(HansServer_Request_Handler)handler;

-(void)postURL:(NSString *)urlpath with:(NSDictionary *)dict withHandler:(HansServer_Request_Handler)handler;

-(NSURLSessionDataTask * _Nullable )postManyDataURL:(NSString *)urlpath body:(NSDictionary *)bodyDictionary  withHandler:(HansServer_Request_Handler)post_handler withProgress:(HansServer_Progress)progressHandler;

-(NSURLSessionDataTask * _Nullable )postDataURL:(NSString *)urlpath data:(NSData *)data fileName:(NSString *)filename datakey:(NSString *)datatag withHandler:(HansServer_Request_Handler)handler withProgress:(HansServer_Progress)progressHandler;

//return NSDjangoAppleUserObject when success.
//return nil when not login etc.
-(void)who:(HansServer_Who_Handler)handler;

-(BOOL)loginUserName:(NSString *)username password:(NSString *)password WithHandler:(HansServer_Login_Handler)handler;
-(BOOL)signupUserName:(NSString *)username password:(NSString *)password WithHandler:(HansServer_Login_Handler)handler;
-(void)logoutWithHandler:(HansServer_Logout_Handler)handler;
-(BOOL)resetPassowrd:(NSString *)email withHandler:(HansServer_Request_Handler)handler;

//load apple user's information, user will be create when userID NOT exist in server
-(BOOL)hansiOSUserLoad:(NSString *)userID accessToken:(NSString * _Nullable)accessToken refreshToken:(NSString * _Nullable)refreshToken firstName:(NSString * _Nullable)firstName lastName:(NSString *_Nullable)lastName email:(NSString * _Nullable)email withHandler:(HansServer_Login_Handler)loginHandler;

//更新用户的信息，value 是更新的结果，key是更新的
-(void)updateUserString:(NSString *)value forKey:(NSString *)key;

//更新用户头像
-(void)updateUserFace:(NSData *)faceData;

//提示其他用户
-(BOOL)notificationUserID:(NSString *)userID withTitle:(NSString *)title text:(NSString * _Nullable )text;

//
-(BOOL)loadUserFace:(NSString *)userID withHandler:(HansServer_UserFace_Handler)handler;

-(BOOL)canRegisterUserName:(NSString *)tryUserName withHandler:(HansServer_Check_Username_Handler)handler;

-(BOOL)registerUserName:(NSString *)username password:(NSString *)password handler:(HansServer_Register_Handler)handler;

//for Share Extension App groups.
// set django account in main app
//return success
-(BOOL)shareExtensionUpdateAppGroupsIdentifier:(NSString *)appGroupsIdentifier;

//load django account in Share Extersion app
//return Load_ShareExtension_Result 
-(Load_ShareExtension_Result)shareExtensionLoadAppGroupsIdentifier:(NSString *)appGroupsIdentifier;
@end
NS_ASSUME_NONNULL_END

