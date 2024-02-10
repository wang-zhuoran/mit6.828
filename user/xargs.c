#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAXSZ 512

enum state
{
    S_WAIT,         // 等待参数输入，此状态为初始状态或当前字符为空格
    S_ARG,          // 参数内
    S_ARG_END,      // 参数结束
    S_ARG_LINE_END, // 左侧有参数的换行，例如"arg\n"
    S_LINE_END,     // 左侧为空格的换行，例如"arg  \n""
    S_END           // 结束，EOF
};

enum char_type
{
    C_SPACE,    // 空格
    C_CHAR,     // 字符
    C_LINE_END, // 换行
}

enum char_type
get_char_type(char c)
{
    switch (c)
    {
    case ' ':
        return C_SPACE;
        break;
    case '\n':
        return C_LINE_END;
        break;
    default:
        return C_CHAR;
        break;
    }
}

/**
 * @brief 状态转换
 *
 * @param cur 当前的状态
 * @param ct 将要读取的字符
 * @return enum state 转换后的状态
 */
enum state transform_state(enum state cur, enum char_type ct)
{
    switch (cur)
    {
    case S_WAIT:
        if (ct == C_SPACE)
        {
            return S_WAIT;
        }
        if (ct == C_CHAR)
        {
            return S_ARG;
        }
        if (ct == C_LINE_END)
        {
            return S_LINE_END;
        }
        break;
    case S_ARG:
        if (ct == C_SPACE)
        {
            return S_ARG_END;
        }
        if (ct == C_CHAR)
        {
            return S_ARG;
        }
        if (ct == C_LINE_END)
        {
            return S_ARG_LINE_END;
        }
        break;
    case S_ARG_END:
    case S_ARG_LINE_END:
    case S_LINE_END:
        if (ct == C_SPACE)
        {
            return S_WAIT;
        }
        if (ct == C_CHAR)
        {
            return S_ARG;
        }
        if (ct == C_LINE_END)
        {
            return S_LINE_END;
        }
    default:
        break;
    }
    return S_END;
}

int main(int argc, char *argv[])
{
}