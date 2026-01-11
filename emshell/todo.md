help和典型命令行的行为不一致：
1. 最后一个token敲错，仍然会继续帮助，而不是报错找不到key
2. 在prefix模式下，无法为最后一个token补全，而是补全下一个token