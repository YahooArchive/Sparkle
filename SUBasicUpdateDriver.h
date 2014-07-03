//
//  SUBasicUpdateDriver.h
//  Sparkle,
//
//  Created by Andy Matuschak on 4/23/08.
//  Copyright 2008 Andy Matuschak. All rights reserved.
//
// Additions by Yahoo:
// Copyright 2014 Yahoo Inc. Licensed under the project's open source license.
//


#ifndef SUBASICUPDATEDRIVER_H
#define SUBASICUPDATEDRIVER_H

#import <Cocoa/Cocoa.h>
#import "SUUpdateDriver.h"
#import "SUUnarchiver.h"
#import "SUAppcast.h"

@class SUAppcastItem, SUHost;
@interface SUBasicUpdateDriver : SUUpdateDriver<NSURLDownloadDelegate, SUUnarchiverDelegate, SUAppcastDelegate> {
	SUAppcastItem *updateItem;
	SUAppcastItem *nonDeltaUpdateItem;
	
	NSURLDownload *download;
	NSString *downloadPath;
	NSString *tempDir;
	
	NSString *relaunchPath;
    
    NSURLConnection*    urlConnection;
    NSMutableData*      downloadedData;
    
    NSString*           resumeDataFile;
    
    NSTimer*            downloadTimer;
    NSUInteger          downloadRetryCounter;
    NSUInteger          downloadRetryInterval;
    NSUInteger          downloadMaxRetries;
    
}

- (void)checkForUpdatesAtURL:(NSURL *)URL host:(SUHost *)host;

- (BOOL)isItemNewer:(SUAppcastItem *)ui;
- (BOOL)hostSupportsItem:(SUAppcastItem *)ui;
- (BOOL)itemContainsSkippedVersion:(SUAppcastItem *)ui;
- (BOOL)itemContainsValidUpdate:(SUAppcastItem *)ui;
- (void)didFindValidUpdate;
- (void)didNotFindUpdate;

- (void)downloadUpdate;

- (void)extractUpdate;
- (void)unarchiverDidFinish:(SUUnarchiver *)ua;
- (void)unarchiverDidFail:(SUUnarchiver *)ua;
- (void)failedToApplyDeltaUpdate;

- (void)installWithToolAndRelaunch:(BOOL)relaunch;
- (void)installWithToolAndRelaunch:(BOOL)relaunch displayingUserInterface:(BOOL)showUI;
- (void)installerForHost:(SUHost *)host failedWithError:(NSError *)error;

- (void)cleanUpDownload;

- (void)abortUpdate;
- (void)abortUpdateWithError:(NSError *)error;

@end

#endif
