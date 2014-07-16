//
//  B.m
//  MessagePassing
//
//  Created by Tom Hu on 7/16/14.
//  Copyright (c) 2014 Tom Hu. All rights reserved.
//

#import "B.h"

@implementation B

- (void)test {
    BOOL test1 = [self.superclass instancesRespondToSelector:@selector(stkClassMethod)];
    BOOL test2 = [self.superclass instancesRespondToSelector:@selector(stkInstanceMethod)];
    BOOL test3 = [super respondsToSelector:@selector(stkClassMethod)];
    BOOL test4 = [super respondsToSelector:@selector(stkInstanceMethod)];
    BOOL test5 = [self.superclass respondsToSelector:@selector(stkClassMethod)];
    BOOL test6 = [self.superclass respondsToSelector:@selector(stkInstanceMethod)];
    
    NSLog(@"%d %d %d %d %d %d", test1, test2, test3, test4, test5, test6);
}

+ (void)testClass {
    BOOL test1 = [self.superclass instancesRespondToSelector:@selector(stkClassMethod)];
    BOOL test2 = [self.superclass instancesRespondToSelector:@selector(stkInstanceMethod)];
    BOOL test3 = [super respondsToSelector:@selector(stkClassMethod)];
    BOOL test4 = [super respondsToSelector:@selector(stkInstanceMethod)];
    BOOL test5 = [self.superclass respondsToSelector:@selector(stkClassMethod)];
    BOOL test6 = [self.superclass respondsToSelector:@selector(stkInstanceMethod)];
    
    NSLog(@"%d %d %d %d %d %d", test1, test2, test3, test4, test5, test6);
}

@end
