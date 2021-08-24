//
//  NSMov2Mp4.h
//  test
//
//  Created by jia yu on 2021/7/31.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
/* Demo Code
 
 
 NSURL *url = [NSURL fileURLWithPath:[NSBundle.mainBundle pathForResource:@"test" ofType:@"MOV"]];
 NSMov2Mp4 *cov = [[NSMov2Mp4 alloc] init];
 NSString *basePath = [NSHomeDirectory() stringByAppendingString:@"/Documents/"];
 NSString *outputFile = [basePath stringByAppendingPathComponent:@"output.mp4"];
 if ([NSFileManager.defaultManager fileExistsAtPath:outputFile]){
     [NSFileManager.defaultManager removeItemAtPath:outputFile error:nil];
 }
 [cov convertMovSourceURL:url resultFile:outputFile withHandler:^(BOOL completed, float progress, NSError * _Nullable error) {
     NSLog(@"Progress: %.1f%%", progress * 100.f);
     if (completed){
         NSLog(@"Completed.");
         dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.1f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
             UIImage *image = nil;
             float duration = 0.f;
             [cov mp4Information:[NSURL fileURLWithPath:outputFile] image:&image duration:&duration];
             NSLog(@"Thumbnail image width:%.0f height:%.0f.",image.size.width,image.size.height);
             NSLog(@"Video duration:%.1f sec",duration);
             UIImageView *i = [[UIImageView alloc] initWithImage:image];
             i.contentMode = UIViewContentModeScaleAspectFit;
             [i setFrame:CGRectMake(0.f, 0.f, 200.f, 200.f)];
             [self.view addSubview:i];
         });
     }
 }];

 */


typedef void (^NSMov2Mp4_Handler) (BOOL completed, float progress, NSError * _Nullable error);

NS_ASSUME_NONNULL_BEGIN
@interface NSMov2Mp4 : NSObject
-(void)convertMovSourceURL:(NSURL *)sourceUrl resultFile:(NSString *)resultFile withHandler:(NSMov2Mp4_Handler)handler;

//return YES is success
//image is 0 second photo
-(BOOL)mp4Information:(NSURL *)mp4FileURL image:(UIImage * _Nullable * _Nullable)image duration:(float *)seconds;
@end
NS_ASSUME_NONNULL_END


