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
  - `ecall`(Environment Call)命令で一つ下のレイヤーへ処理を依頼する
    - CPUが1つ下のモード(=1つ上の権限)に切り替わり、終わった後もとに戻る
