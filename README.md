# Oni-Gokko
本ゲームは大学の授業で制作したC言語で書かれたコンソールゲームです．  
ncursesを使用しています．  

# ゲーム概要

敵からひたすら逃げてください．  
敵は増殖します．  
敵は賢いので20歩くと幅優先探索で迫ってきます．学習するんですね．(いいえ)  

# 使い方
```text
# インストール
$ git clone https://github.com/mkan0141/Kuso-Game

# 実行
$ make
$ ./oni
```

# 使用アルゴリズム
敵AIに幅優先探索  
迷路の自動生成に壁伸ばし法
