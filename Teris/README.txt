俄罗斯方块 · 阶段一（控制台版）骨架
=====================================================================

★ 这是什么：一份"只有骨架"的工程。
  .h 里类怎么切、成员叫什么、哪个函数是虚函数 —— 全部写好了，这是你要参考的部分。
  .cpp 里所有函数体都是空的，只有签名 + 注释（该做什么、有什么坑）。
  实现全部由你自己敲。

  本机已用 MinGW-w64 实测：骨架本身零错误零警告编译通过。
  也就是说你现在 Ctrl+Shift+B 就能编出来，只是跑起来什么都不显示 ——
  每填完一个函数重新编一次，你能一步步看到它活过来。


一、文件清单与每个类的职责
---------------------------------------------------------------------
Types.h              两个小类型：IPoint（格子坐标）、CellKind（格子里是什么）
                      还有 PieceKind（七种方块的编号）

Board.h / .cpp       【纯数据 + 规则】10x20 的格子
                      只回答"能不能放""怎么消行"，不画东西、不认识窗口

Piece.h / .cpp       【抽象基类】所有方块的共同行为
                      移动 / 下落 / 旋转 / 硬降 写在基类；
                      "我长什么样"由派生类通过纯虚 Cells() 回答

StandardPiece.h/.cpp 【派生类】标准七种方块，共用一张形状表 SHAPES
                      只有数据不同，所以一个类搞定，不给每种方块写一个类

IRenderer.h          【抽象基类】规定"要画哪些东西"，不关心画到哪里

ConsoleRenderer.h/.cpp 【派生类】用 cout 把棋盘画到控制台
                      阶段二换成 GdiRenderer 时，Game 一行都不用改

Game.h / .cpp        【中枢】持有棋盘、当前方块、渲染器，负责调度
                      什么时候掉一格、掉不动了怎么办、按键怎么响应

main.cpp             入口：主循环 = 读键盘 + 到点下落 + 画一帧

.vscode/tasks.json   Ctrl+Shift+B 直接编译（已配好中文编码参数）
.gitignore           忽略 exe / o 文件


二、成员函数速查（.h 里有完整声明，这里只列职责）
---------------------------------------------------------------------
Board
  Clear()            清空棋盘
  At(x,y)            读一格；越界返回 EMPTY
  IsEmpty(x,y)       这一格能不能放（注意：y<0 放行，方块从界外飘进来）
  CanPlace(cells,n)  这一组格子整体放得下吗  ← 碰撞判定唯一入口
  Lock(cells,n,c)    方块落地，把格子写进棋盘
  ClearFullRows()    扫一遍消行，返回消了几行
  IsTopOut(cells,n)  新方块一出生就重叠 → 顶死
  私有：RowFull(y)、RemoveRow(y)

Piece（抽象）
  Cells(out,n)       纯虚：我当前占哪几格（世界坐标）
  Color()            纯虚：我什么颜色
  Clone()            纯虚：复制一个我（返回的指针你要自己 delete）
  Rotate(b,ccw)      虚：转 90 度，转不开时自动踢墙，实在不行回滚
  TryMove(b,dx,dy)   试着平移，能移才真移
  TryFall(b)         试着掉一格，返回 false 表示到底了
  HardDrop(b)        一路砸到底，返回掉了几格
  Pos()              我在哪

StandardPiece
  Cells(out,n)       查 SHAPES[m_kind][m_rotation] 再叠加自己的位置
  Color()            把 PieceKind 换算成 CellKind
  Clone()            new 一个同种类同位置同姿态的

IRenderer
  BeginFrame() / EndFrame()   一帧的开始和结束
  DrawPiece(p)       画正在掉的方块（★ 内部会虚调用 p.Cells）
  DrawBoard(b)       画棋盘
  DrawPanel(...)     画分数行
  DrawMessage(text)  画提示文字

Game
  Init(renderer)     传入渲染器（★ 换 GDI 只改 main.cpp 这一行）
  Update()           走一步：掉一格；掉不动就 LockCurrent
  Render()           画一帧
  HandleKey(key)     a/d 左右，w 旋转，s 下移，空格 直落
  SpawnPiece()       生成新方块（顺便判断顶死）
  LockCurrent()      写进棋盘 → 消行 → 计分 → 换下一个
  FallIntervalMs()   当前等级下多少毫秒掉一格（等级越高越快）
  私有：SpawnPos()、MakeRandomPiece()


三、建议的填写顺序（每填完一批就编一次，别一口气全写）
---------------------------------------------------------------------
第 1 批：Board.cpp 全部
  这是最独立的一块，不依赖任何别的类。写完了可以自己在 main 里
  手工造几组 IPoint 测一下 CanPlace / ClearFullRows 对不对。

第 2 批：StandardPiece.cpp 的 SHAPES 表 + Cells()
  先只填 I 和 O 两种，其它留着占位。此时可以在 main 里 new 一个
  StandardPiece 然后把四格坐标 cout 出来看对不对。
  ★ 形状表是整个项目唯一需要你在纸上画的东西，别在脑子里转。

第 3 批：Piece.cpp 全部
  TryMove / TryFall / HardDrop / Rotate。
  这块的验货标准：方块能左右挪、掉到底会停住、贴墙能踢着转。

第 4 批：ConsoleRenderer.cpp 全部
  先让棋盘能打印出来（哪怕只有固定格子），再叠上方块覆盖层。

第 5 批：Game.cpp 全部 + main.cpp 主循环
  到这里第一次能真正"玩"。

填完每批编译一次的好处：报错永远只会指向你刚写的那几个函数，
不会出现"一次改了 200 行，然后面对 30 条报错不知道从哪查"。


四、三个必须亲眼验证的点（书上讲不清，跑一遍才懂）
---------------------------------------------------------------------
1) 虚析构
   在 Piece 和 StandardPiece 的析构里各加一句 cout，
   然后把 Piece.h 里 ~Piece() 前面的 virtual 删掉，重新编译运行。
   你会看到派生类的析构根本没被调用。这就是"为什么基类析构必须是 virtual"。

2) 虚调用真的发生了
   在 StandardPiece::Cells 里加一句 cout << "StandardPiece::Cells\n";
   然后跑游戏。你会发现 Piece::TryMove（基类的代码）里调出来的
   却是派生类的实现 —— 基类写算法、派生类补细节，这就是套路。

3) _kbhit 为什么不能换成 cin
   把 main.cpp 里的 _kbhit() 判断去掉，直接 _getch()。
   程序会卡在等你按键，方块一动不动。
   这个现象记住，阶段二学 Win32 的 PeekMessage 时你会再见它一次。


五、编译与运行
---------------------------------------------------------------------
VSCode：Ctrl+Shift+B（tasks.json 已配好）

手敲：
  g++ -std=c++17 -Wall -g -finput-charset=UTF-8 -fexec-charset=GBK ^
      main.cpp Board.cpp Piece.cpp StandardPiece.cpp ConsoleRenderer.cpp Game.cpp ^
      -o tetris.exe

  （^ 是 Windows cmd 的续行符；PowerShell 里换成 ` 反引号）

-finput-charset=UTF-8 -fexec-charset=GBK 这两个参数别删，
否则源码里的中文在 Windows 控制台会变成乱码。


六、操作键位（你自己定，HandleKey 里改）
---------------------------------------------------------------------
建议：A / D 左右，W 旋转，S 下落一格，空格 直落，Q 退出


七、下一步（阶段二）
---------------------------------------------------------------------
逻辑跑通并且你确认消行、旋转、顶死都正确之后：
  1. 新建 GdiRenderer.h/.cpp，继承 IRenderer，用 FillRect 画格子
  2. main.cpp 里把 ConsoleRenderer 换成 GdiRenderer —— 只改一行
  3. 再补 Window 类封装 HWND / WndProc / 消息泵
  4. 最后加 CreateCompatibleDC + BitBlt 双缓冲解决闪烁
