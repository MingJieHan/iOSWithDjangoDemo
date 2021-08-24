//
//  NSArticleObject.h
//  HansArticle
//
//  Created by jia yu on 2021/7/28.
//

#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN
@interface NSArticleImageObject : NSObject
@property (nonatomic) UIImage * _Nullable image;
@property (nonatomic) NSString * _Nullable text;
@property (nonatomic) NSDictionary * _Nullable imageDictionary;
@property (nonatomic) NSString * _Nullable latitude;
@property (nonatomic) NSString * _Nullable longitude;
@property (nonatomic) NSString * _Nullable altitude;
@property (nonatomic) BOOL textChanged; //default is NO
@end
NS_ASSUME_NONNULL_END
