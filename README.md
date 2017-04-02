# NSTimer-Block
Add block ability to NSTimer to avoid common retain cycle issues.

## What Retain Cycle
It is very common that retain cycle occurs while using NSTimer. A general scenario is that
you own a timer, set timer's target to `self`, then boom!

What?

Yes, here's the detail:
- You own a timer, which means you have strong reference to it.
- You set timer's target to `self`, which means the timer has strong reference to you.
- See? That's the retain cycle. The retain cycle won't break unless you `invalidate` the timer.
- It's useless to call `invalidate` in your `dealloc` method, because you won't be released and your `dealloc` won't have the chance to get called.

## How To Avoid
There are two common solutions: one is to set a `proxy (middleman)` between the target and the timer, the other one is to use `block`. This tiny library implements the `block` solution.

## How To Use
There are only two class methods.

```objc
+ (NSTimer *)cht_scheduledTimerWithTimeInterval:(NSTimeInterval)interval repeats:(BOOL)repeats block:(void (^)(NSTimer *timer))block;
+ (NSTimer *)cht_timerWithTimeInterval:(NSTimeInterval)interval repeats:(BOOL)repeats block:(void (^)(NSTimer *timer))block;
```

Now you can use common `weak-strong dance` to avoid retain cycle.

```objc
- (void)viewDidLoad {
    [super viewDidLoad];
    __weak typeof(self)weakSelf = self;
    self.timer = [NSTimer cht_scheduledTimerWithTimeInterval:0.5 repeats:YES block:^(NSTimer *timer) {
        __strong typeof(weakSelf)self = weakSelf;
        if (!self) return;
        [self doWhateverYouWant];
    }];
}

- (void)dealloc {
    [_timer invalidate];
    _timer = nil;
}
```

Apple provides following APIs in iOS 10:
- `+ scheduledTimerWithTimeInterval:repeats:block:`
- `+ timerWithTimeInterval:repeats:block:`

As you can see, these APIs have same signatures as mine, except they don't have prefix. So you can use this tiny library when you still need to support previous iOS version. When your minimum supported iOS version bumps to 10 or higher, you only have to remove the `cht_` prefix.

## References
- [objective c - Weak Reference to NSTimer Target To Prevent Retain Cycle - Stack Overflow](http://stackoverflow.com/questions/16821736/weak-reference-to-nstimer-target-to-prevent-retain-cycle)
- [iOS 中的 NSTimer | Why's Blog](https://blog.callmewhy.com/2015/07/06/weak-timer-in-ios/)
- [如何打破NSTimer与Target之间的Retain Cycle - 简书](http://www.jianshu.com/p/90da2623fc04)
