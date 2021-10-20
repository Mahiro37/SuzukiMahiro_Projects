◇外部ファイルで編集できる値(すべて初期値)◇

●01_player.txt [プレイヤー] ※最大生成数＆種類数２
  - TYPE <種類(プレイヤー１＝０,プレイヤー２＝１)>
  - POS <位置>
  - SIZE <大きさ>
  - ROT <角度>
  - MOVE <移動量>
  - BULLET_TYPE <弾の種類>

●02_bullet.txt [弾] ※最大種類数５
  - TYPE <種類>
  - DISTANCE <生成位置(プレイヤーの中心からの距離)>
  - SIZE <モデルの大きさ>
  - MOVE <移動量>
  - LIFE <反射数>

●03_BLOCK.txt [障害物] ※最大生成数３２
  - POS <位置>
  - SIZE <大きさ(XとZは同じ値)>
  - ROT <角度>
  
●04_wall.txt [壁] ※最大生成数３２
  - TYPE <種類(奥壁＝１,右＝２,手前＝３,左＝４)>
  - POS <位置>
  - SIZE <大きさ>
  - ROT <角度>
  
●03_BLOCK.txt [床] ※最大生成数３２
  - POS <位置>
  - SIZE <大きさ>
  - ROT <角度>
  