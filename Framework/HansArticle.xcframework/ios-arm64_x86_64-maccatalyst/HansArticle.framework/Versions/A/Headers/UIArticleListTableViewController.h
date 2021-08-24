//
//  UIArticleListTableViewController.h
//  iOSWithDjango
//
//  Created by jia yu on 2020/12/20.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
extern NSBundle *HansArticleBundle;
//NSLocalizedStringFromTableInBundle(@"Loading...", @"HansArticle", HansArticleBundle, nil);

@interface UIArticleListTableViewController : UITableViewController
@property (nonatomic) BOOL isMySelfOnly;
@property (nonatomic) UIColor *tintColor;
@property (nonatomic) NSString *refreshTitle;
@end
NS_ASSUME_NONNULL_END
