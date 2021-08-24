//
//  UIArticleViewController.h
//  iOSWithDjango
//
//  Created by jia yu on 2020/12/20.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIArticleViewController : UIViewController
@property (nonatomic) NSDictionary *articleDictionary;

-(void)openArticleID:(NSString *)articleID WithTitle:(NSString *)title text:(NSString *)text;
@end

NS_ASSUME_NONNULL_END
