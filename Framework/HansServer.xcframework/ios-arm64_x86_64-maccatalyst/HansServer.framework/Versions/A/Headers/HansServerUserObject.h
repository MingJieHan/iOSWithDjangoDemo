//
//  NSDjangoAppleUserObject.h
//  django
//
//  Created by Han Mingjie on 2020/12/11.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN
@interface HansServerUserObject : NSObject
@property (nonatomic,readonly) NSString *accountID;
@property (nonatomic,readonly) NSString *username;
@property (nonatomic) NSString *firstName;
@property (nonatomic) NSString *lastName;
@property (nonatomic) NSString *email;
@property (nonatomic,readonly) BOOL email_verify;
@property (nonatomic) NSString *nickName;
@property (nonatomic) NSString *mobile;
@property (nonatomic,readonly) BOOL mobile_verify;
@property (nonatomic) NSString *whatup;
@property (nonatomic) NSData *face;
@property (nonatomic,readonly) NSMutableArray <NSDictionary *>*devicesArray;

-(id)initWithDictionary:(NSDictionary *)dict;
-(BOOL)isDjangoUser;
-(BOOL)isAppleIDUser;
@end
NS_ASSUME_NONNULL_END
