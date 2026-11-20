# MEMO

- OpenSBIはブートローダー・ファームウェア
  - ハードウェアとOSの間を取り持つ
  - PCのBIOSやUEFIに近い
  - OS起動後もバックグラウンドに常駐し、OSからのシステムコールに応答し続ける
  - RISC-VのSBI(Supervisor Binary Interface)という仕様のオープン実装
  - ハードウェアの違いを吸収する抽象層らしい
- RISC-Vのモード
  - Uモード(User Mode): 普通のアプリが動くモード
  - Sモード(Supervisor Mode): OSカーネルが動くモード
  - Mモード(Machine Mode): ハードウェアを直接触る、最も権限が強いモード。OpenSBIはここ
