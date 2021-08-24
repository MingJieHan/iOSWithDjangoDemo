//
//  LoginViewController.h
//  HansServer
//
//  Created by jia yu on 2021/7/20.
//

#import <UIKit/UIKit.h>
#import <HansServer/HansServerHandler.h>

NS_ASSUME_NONNULL_BEGIN
@interface HansLoginViewController : UIViewController
@property (nonatomic) UIView *titleView;
@property (nonatomic) UIColor *boardColor;
@property (nonatomic) UIColor *boardCurrentColor;
@property (nonatomic) UIColor *signatureColor;
@property (nonatomic) UIColor *loginColor;
@property (nonatomic) NSString *companyName;
@property (nonatomic) NSString *serviceURLString;       //default is /static/TermsOfService.pdf
@property (nonatomic) NSString *policyURLString;        //default is /static/PrivacyPolicy.pdf
@property (nonatomic) HansServer_Login_Handler loginHandler;

+(HansLoginViewController *)shareWithHandler:(HansServer_Login_Handler)loginHandler;
@end
NS_ASSUME_NONNULL_END
