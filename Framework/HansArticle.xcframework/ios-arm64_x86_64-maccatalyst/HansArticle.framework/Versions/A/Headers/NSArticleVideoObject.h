//
//  NSArticleObject.h
//  HansArticle
//
//  Created by jia yu on 2021/7/28.
//

#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN
@interface NSArticleVideoObject : NSObject
@property (nonatomic) NSString * _Nullable videoFile;
@property (nonatomic) float duration;
@property (nonatomic) CGSize videoSize;
@property (nonatomic) NSString * _Nullable device;
@property (nonatomic) NSString * _Nullable software;
@property (nonatomic) NSDate * _Nullable date;
@property (nonatomic) NSString * _Nullable latitude;
@property (nonatomic) NSString * _Nullable longitude;
@property (nonatomic) NSString * _Nullable altitude;
@property (nonatomic) UIImage * _Nullable thumbnail;
@property (nonatomic) NSString * _Nullable text;
@property (nonatomic) NSDictionary * _Nullable videoDictionary;
@property (nonatomic) BOOL textChanged;     //default is NO
@end
NS_ASSUME_NONNULL_END
