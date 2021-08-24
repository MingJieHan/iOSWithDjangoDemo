//
//  UIAccountViewController.m
//  iOSWithDjango
//
//  Created by jia yu on 2020/12/23.
//

#import "AppDelegate.h"
#import "UIAccountTableViewController.h"
#import <HansServer/HansServer.h>
#import <HansArticle/HansArticle.h>


#define CELL_IDENTIFIER_LOGIN @"CELL_IDENTIFIER_LOGIN"
#define CELL_IDENTIFIER_LOGOUT @"CELL_IDENTIFIER_LOGOUT"
#define CELL_IDENTIFIER_DETAIL @"CELL_IDENTIFIER_DETAIL"
#define CELL_IDENTIFIER_CACHE @"CELL_IDENTIFIER_CACHE"

@interface UIAccountTableViewController ()<UITableViewDelegate,UITableViewDataSource>{
    HansLoginViewController *loginViewController;
    NSString *currentAppString;
    NSMutableArray <NSIndexPath *>*requireFreshIndexPaths;
}
@end

@implementation UIAccountTableViewController

-(id)initWithStyle:(UITableViewStyle)style{
    self = [super initWithStyle:style];
    if (self){
        self.tableView.delegate = self;
        self.tableView.dataSource = self;
    }
    return self;
}

- (id)initWithCoder:(NSCoder *)coder{
    self = [super initWithCoder:coder];
    if (@available(iOS 13.0, *)) {
        self = [super initWithStyle:UITableViewStyleInsetGrouped];
    } else {
        self = [super initWithStyle:UITableViewStyleGrouped];
    }
    if (self){
        self.tableView.separatorStyle = UITableViewCellSeparatorStyleSingleLine;
        self.tableView.delegate = self;
        self.tableView.dataSource = self;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(currentUserChanged:) name:Current_User_Changed_Notification_Name object:nil];
}

-(void)dealloc{
    [NSNotificationCenter.defaultCenter removeObserver:self];
}

-(void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
    
    if (nil == currentAppString){
        NSString *version = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
        NSString *build = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"];
    #ifdef DEBUG
        version = [NSString stringWithFormat:@"DEBUG %@",version];
    #endif
        NSString *http = @"http";
        if (HansServer.shareServer.requestHttps){
            http = @"https";
        }
        NSString *port = @"";
        if (HansServer.shareServer.port != 80 && HansServer.shareServer.port != 443){
            port = [NSString stringWithFormat:@":%ld",(long)HansServer.shareServer.port];
        }
        currentAppString = [NSString stringWithFormat:@"\n%@(%@) %@://%@%@",
                          version,build,http,
                          HansServer.shareServer.server,port];
    }
    [self.tableView reloadData];
    
    NSIndexPath *cacheIndexPath = [NSIndexPath indexPathForRow:0 inSection:0];
    [self.tableView reloadRowsAtIndexPaths:@[cacheIndexPath] withRowAnimation:UITableViewRowAnimationFade];
    
    if (requireFreshIndexPaths.count > 0){
        [self.tableView reloadRowsAtIndexPaths:requireFreshIndexPaths withRowAnimation:UITableViewRowAnimationFade];
    }
    [requireFreshIndexPaths removeAllObjects];
    return;
}

-(void)emptyCacheAction{
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:NSLocalizedString(@"Clean Cache?", nil)  message:NSLocalizedString(@"Do you want to clean caches? this app will faster with caches.", nil) preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *clean = [UIAlertAction actionWithTitle:NSLocalizedString(@"Clean", nil)  style:UIAlertActionStyleDestructive handler:^(UIAlertAction * _Nonnull action) {
        [HansCache.shareHansCache clean];
        [self.tableView reloadRowsAtIndexPaths:@[[NSIndexPath indexPathForRow:0 inSection:0]] withRowAnimation:UITableViewRowAnimationFade];
    }];
    [alert addAction:clean];
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:NSLocalizedString(@"Cancel", nil)  style:UIAlertActionStyleCancel handler:nil];
    [alert addAction:cancel];
    [self presentViewController:alert animated:YES completion:nil];
    return;
}

-(void)currentUserChanged:(NSNotification *)_notification{
    [self.tableView reloadData];
}

-(void)detailAccountAction{
    HansAccountDetailTableViewController *v = [[HansAccountDetailTableViewController alloc] init];
    v.user = HansServer.shareServer.currentUser;
    [self.navigationController pushViewController:v animated:YES];
}

-(void)loginAction{
    UIAccountTableViewController * __strong strongSelf = self;
    loginViewController = [HansLoginViewController shareWithHandler:^(BOOL success, HansServerUserObject * _Nullable user, NSString * _Nullable error) {
        [HansServer.shareServer shareExtensionUpdateAppGroupsIdentifier:@"group.djangoServer"];
        [strongSelf->loginViewController dismissViewControllerAnimated:YES completion:nil];
    }];
    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:loginViewController];
    nav.modalPresentationStyle = UIModalPresentationFullScreen;
    nav.navigationBar.translucent = NO;
    [self presentViewController:nav animated:YES completion:nil];
}

-(void)logoutAction{
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:NSLocalizedString(@"Log Out", nil) message:NSLocalizedString(@"Do you want to logout?", nil) preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *cAction = [UIAlertAction actionWithTitle:NSLocalizedString(@"Log Out", nil) style:UIAlertActionStyleDestructive handler:^(UIAlertAction * _Nonnull action) {
        [HansServer.shareServer logoutWithHandler:^(BOOL success, NSString * _Nullable error) {
            if (success){
                [HansServer.shareServer shareExtensionUpdateAppGroupsIdentifier:@"group.djangoServer"];
            }else{
                NSLog(@"Log Out error.");
            }
        }];
    }];
    [alert addAction:cAction];
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:NSLocalizedString(@"Cancel", nil) style:UIAlertActionStyleCancel handler:nil];
    [alert addAction:cancelAction];
    [self presentViewController:alert animated:YES completion:nil];
    return;
}

-(NSString *)cellIdentifierFor:(NSIndexPath *)indexPath{
    switch (indexPath.section) {
        case 0:
            return CELL_IDENTIFIER_CACHE;
        case 1:
            if (nil == HansServer.shareServer.currentUser){
                return CELL_IDENTIFIER_LOGIN;
            }else{
                switch (indexPath.row) {
                    case 0:
                        return CELL_IDENTIFIER_DETAIL;
                    case 1:
                        return CELL_IDENTIFIER_LOGOUT;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }
    return nil;
}

#pragma mark - UITableViewDelegate,UITableViewDataSource
-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return 2;
}
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    switch (section) {
        case 0:
            return 1;
        case 1:
            if (nil != HansServer.shareServer.currentUser){
                return 2;
            }else{
                return 1;
            }
        default:
            break;
    }
    return 0;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    NSString *identifier = [self cellIdentifierFor:indexPath];
    UITableViewCell *cell = nil;
    if ([identifier isEqualToString:CELL_IDENTIFIER_LOGOUT]){
        cell = [tableView dequeueReusableCellWithIdentifier:identifier];
        if (nil == cell){
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:identifier];
            cell.accessoryType = UITableViewCellAccessoryNone;
            cell.textLabel.textAlignment = NSTextAlignmentCenter;
            cell.textLabel.text = NSLocalizedString(@"Log Out", nil);
        }
    }else if ([identifier isEqualToString:CELL_IDENTIFIER_LOGIN]){
        cell = [tableView dequeueReusableCellWithIdentifier:identifier];
        if (nil == cell){
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:identifier];
            cell.accessoryType = UITableViewCellAccessoryNone;
            cell.textLabel.textAlignment = NSTextAlignmentCenter;
            cell.textLabel.text = NSLocalizedString(@"Log In", nil);
        }
    }else if ([identifier isEqualToString:CELL_IDENTIFIER_DETAIL]){
        cell = [tableView dequeueReusableCellWithIdentifier:identifier];
        if (nil == cell){
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:identifier];
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
            cell.textLabel.text = NSLocalizedString(@"Details", nil);
        }
        if (HansServer.shareServer.currentUser.nickName){
            cell.detailTextLabel.text = HansServer.shareServer.currentUser.nickName;
        }else{
            cell.detailTextLabel.text = HansServer.shareServer.currentUser.email;
        }
    }else if ([identifier isEqualToString:CELL_IDENTIFIER_CACHE]){
        cell = [tableView dequeueReusableCellWithIdentifier:identifier];
        if (nil == cell){
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:identifier];
            cell.accessoryType = UITableViewCellAccessoryNone;
            cell.textLabel.text = NSLocalizedString(@"Cache Size", nil);
        }
        cell.detailTextLabel.text = [HansCache.shareHansCache cacheSizeString];
    }
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    NSString *identifier = [self cellIdentifierFor:indexPath];
    if ([identifier isEqualToString:CELL_IDENTIFIER_LOGOUT]){
        [self logoutAction];
    }else if ([identifier isEqualToString:CELL_IDENTIFIER_LOGIN]){
        [self loginAction];
    }else if ([identifier isEqualToString:CELL_IDENTIFIER_DETAIL]){
        [requireFreshIndexPaths addObject:indexPath];
        [self detailAccountAction];
    }else if ([identifier isEqualToString:CELL_IDENTIFIER_CACHE]){
        [requireFreshIndexPaths addObject:indexPath];
        [self emptyCacheAction];
    }
    return;
}

-(NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section{
    switch (section) {
        case 1:{
            return currentAppString;}
        default:
            break;
    }
    return @"";
}

-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section{
    switch (section) {
        case 0:
            return NSLocalizedString(@"System", nil);
        case 1:
            return NSLocalizedString(@"Account", nil);
        default:
            break;
    }
    return @"";
}
@end
