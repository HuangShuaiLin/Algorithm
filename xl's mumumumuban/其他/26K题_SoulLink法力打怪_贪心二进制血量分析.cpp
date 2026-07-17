#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * ***26省赛第K题 - Soul Link 法力打怪***
 * 题目：n≤30，敌人等级i的血量为2^(i-1)，有a_i个。
 *       消耗m法力给敌人上Soul Link(持续到其死亡)，
 *       消耗1法力Attack：对所有有Soul Link的敌人造成1伤害，
 *       敌人死亡奖励m法力。初始法力不能<0。
 *       求最小初始法力。
 *
 * 算法：贪心 + 二进制位分析
 *       血量 = 2^{i-1} 有特殊的二进制性质
 *       Attack 一次对全体Link敌人各-1血
 *       → 相当于你用m点法力"雇佣"一个敌人，然后每次攻击全体-1
 *       → 攻击 (2^{i-1}) 轮后敌人死亡，返还m法力
 *       → 相当于你先"借"法力上限
 *
 * 核心思路：
 * - 把每级敌人拆成 2^{i-1} 个血量1的1级敌人
 * - 每次 Soul Link + Attack 一轮后: 当前所有Link敌人各-1血
 * - 问题转化为: 有一堆血量为1的敌人，每次花m+1法力杀一批
 * - 最优: 尽可能一次多杀，减少法力峰值
 *
 * 贪心策略：
 * - 从低血量的敌人开始处理
 * - 模拟: 维护当前法力，不足时补足初始法力
 * - 由于 n ≤ 30，总血量 ≤ 2^{30} 太大，只能按位模拟
 */

ll minInitialMana(int n, ll m, const vector<ll>& cnt) {
    // cnt[i] = 等级i+1的敌人数
    // 血量 = 2^i

    ll mana = 0;     // 当前法力
    ll maxNeed = 0;  // 最大需要的初始法力(即最低谷)
    ll linkedHp = 0; // 当前被Link的敌人总血量(抽象)

    // 从低到高处理: 把高级敌人"拆开"来打
    // 但实际中高级敌人只需要一个Soul Link就能一直A到死
    // 关键: 有多少敌人同时被Link，决定了每轮Attack的效率

    // 贪心模拟: 对一个等级i的敌人，需要2^i次Attack+1次Soul Link
    // 成本: m + 2^i (法力消耗) vs 收益: m (死亡返还)
    // 净成本: 2^i

    // 模拟最优调度: 优先处理血少的让法力回流
    ll cumulative = 0;
    for (int i = 0; i < n; i++) {
        if (cnt[i] == 0) continue;
        ll hp = 1LL << i; // 血量 2^i
        ll cost = m;      // Soul Link cost
        // Attack cost = hp (每轮-1)

        // 对于每批敌人,需要维持法力≥0
        // 初期需要 m 法力做 Soul Link
        // 之后每轮-1法力攻击, 尽量并行
        // 当有多个被Link的敌人时, 每轮攻击对所有人生效
        // 所以同时打多个敌人是最优的

        // 简化: mana 不够时就增加 maxNeed
        // 具体需要模拟整个过程
    }

    return maxNeed;
}