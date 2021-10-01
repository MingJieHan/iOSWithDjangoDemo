//
//  AppDelegate.m
//  HansFrameworkDemo
//
//  Created by jia yu on 2021/8/24.
//

#import "AppDelegate.h"


#import <HansServer/HansServer.h>
#import <UserNotifications/UserNotifications.h>
#define DONOT_ASK_OPEN_REMOTE_NOTIFICATON_KEY @"DONOT_ASK_OPEN_REMOTE_NOTIFICATON_KEY"



@interface AppDelegate ()

@end

@implementation AppDelegate
@synthesize window = _window;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    HansRequestManager.defaultHansRequestManager.printLog = YES;

    BOOL server = YES;
//    server = NO;
    //empty cached files
//    [HansCache.shareHansCache clean];
    HansServer *s = HansServer.shareServer;
    if (nil == s){
        NSLog(@"The Framework Certificate expired, please goto https://developer.hanmingjie.com/ request other certificate.");
        return YES;
    }
    
    if (server){
        s.server = @"djangoserver.hanmingjie.com";
        s.port = 443;
        s.requestHttps = YES;
    }else{
        s.server = @"192.168.3.3";
        s.port = 80;
        s.requestHttps = NO;
    }
    
    NSString *f = [NSBundle.mainBundle pathForResource:@"Info" ofType:@"plist"];
    NSDictionary *dict = [[NSDictionary alloc] initWithContentsOfFile:f];
    NSString *identifier = [dict valueForKey:@"CFBundleIdentifier"];
//    NSLog(@"%@",identifier);
    HansServer.shareServer.bundleIdentifierForToken = identifier;
    
#ifdef DEBUG
    HansServer.shareServer.isDevelopmentToken = YES;
#else
    HansServer.shareServer.isDevelopmentToken = NO;
#endif

    [self request_remote_notification];
    
    [HansServer.shareServer who:^(HansServerUserObject * _Nullable user, NSString * _Nullable error) {
        [HansServer.shareServer shareExtensionUpdateAppGroupsIdentifier:@"group.djangoServer"];
    }];
    return YES;
}


#pragma mark - UISceneSession lifecycle


- (UISceneConfiguration *)application:(UIApplication *)application configurationForConnectingSceneSession:(UISceneSession *)connectingSceneSession options:(UISceneConnectionOptions *)options {
    // Called when a new scene session is being created.
    // Use this method to select a configuration to create the new scene with.
    return [[UISceneConfiguration alloc] initWithName:@"Default Configuration" sessionRole:connectingSceneSession.role];
}


- (void)application:(UIApplication *)application didDiscardSceneSessions:(NSSet<UISceneSession *> *)sceneSessions {
    // Called when the user discards a scene session.
    // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
    // Use this method to release any resources that were specific to the discarded scenes, as they will not return.
}

#pragma mark - My Function
-(void)requestRemoteNotificationAuthority{
    [[UNUserNotificationCenter currentNotificationCenter] requestAuthorizationWithOptions:UNAuthorizationOptionBadge|UNAuthorizationOptionAlert|UNAuthorizationOptionSound completionHandler:^(BOOL granted, NSError * _Nullable error) {
        if (granted){
            NSLog(@"Allowed Remote Notification");
            [self registerThisDeviceForRemoteNotification];
        }else{
            NSLog(@"Don't Remote Notification");
        }
    }];
}

-(void)registerThisDeviceForRemoteNotification{
    dispatch_async(dispatch_get_main_queue(), ^{
        [[UIApplication sharedApplication] registerForRemoteNotifications];
    });
}

-(void)tipNoNotification{
    if ([[[NSUserDefaults standardUserDefaults] valueForKey:DONOT_ASK_OPEN_REMOTE_NOTIFICATON_KEY] boolValue]){
        return;
    }
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Remote Notification Disabled" message:@"Please goto Settings -> Notification -> Hans Ltd. -> Allow Notification, and Turn to ON.\n\nClick Cancel to disable this tip." preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *action = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil];
    [alert addAction:action];
    UIAlertAction *dontAction = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
        [NSUserDefaults.standardUserDefaults setValue:[NSNumber numberWithBool:YES] forKey:DONOT_ASK_OPEN_REMOTE_NOTIFICATON_KEY];
        [NSUserDefaults.standardUserDefaults synchronize];
    }];
    [alert addAction:dontAction];
    [UIApplication.sharedApplication.keyWindow.rootViewController presentViewController:alert animated:YES completion:nil];
}

-(void)request_remote_notification{
    [[UNUserNotificationCenter currentNotificationCenter] getNotificationSettingsWithCompletionHandler:^(UNNotificationSettings * _Nonnull settings) {
        switch (settings.authorizationStatus) {
            case UNAuthorizationStatusNotDetermined:
                [self requestRemoteNotificationAuthority];
                break;
            case UNAuthorizationStatusDenied:{
                dispatch_async(dispatch_get_main_queue(), ^{
                    [self tipNoNotification];
                });
                break;}
            case UNAuthorizationStatusAuthorized:
                break;
            case UNAuthorizationStatusProvisional:
                break;
            case UNAuthorizationStatusEphemeral:
                break;
            default:
                break;
        }
    }];
}
@end
