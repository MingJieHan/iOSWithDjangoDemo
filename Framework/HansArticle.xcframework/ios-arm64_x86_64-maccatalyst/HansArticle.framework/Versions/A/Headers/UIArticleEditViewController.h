//
//  UIArticleEditViewController.h
//  iOSWithDjango
//
//  Created by jia yu on 2020/12/25.
//

#import <UIKit/UIKit.h>


typedef NS_ENUM(NSInteger, UIArticleEditViewControllerStyle) {
    UIArticleEditViewControllerStyleHans,           // default style
    UIArticleEditViewControllerStyleWeChat          // liked Wechat sent memont.
};

NS_ASSUME_NONNULL_BEGIN
@interface UIArticleEditViewController:UITableViewController
@property (nonatomic) UIArticleEditViewControllerStyle articleEditStyle;
@property (nonatomic) NSDictionary *articleDictionary;

-(id)initWithImages:(NSArray <UIImage *>*)imagesArray articleTitle:(NSString *)articleTitle articleText:(nullable NSString *)articleText autoSend:(BOOL)autoSend;
@end
NS_ASSUME_NONNULL_END
