//
//  main.m
//  MessagePassing
//
//  Created by Tom Hu on 7/16/14.
//  Copyright (c) 2014 Tom Hu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Sub : NSObject

- (void)print;

@end

@implementation Sub

- (void)print {
    NSLog(@"Sub");
}

@end

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        Sub *sub = [[Sub alloc] init];
        [sub print];
        
        NSObject *test = [[NSObject alloc] init];
        [(Sub *)test print]; // TODO - 仍然未理解
    }
    return 0;
}

