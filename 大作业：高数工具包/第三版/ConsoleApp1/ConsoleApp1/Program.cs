using System;
using System.Linq.Expressions;
using System.Reflection;

namespace Derivative
{
    class Program
    { 
        static Expression GetDerivative(Expression node)
        {
            if (node.NodeType == ExpressionType.Add
                || node.NodeType == ExpressionType.Subtract)
            {   // 加减法 
                BinaryExpression binexp = (BinaryExpression)node;
                Expression dleft = GetDerivative(binexp.Left);
                Expression dright = GetDerivative(binexp.Right);
                BinaryExpression resbinexp;

                if (node.NodeType == ExpressionType.Add)
                    resbinexp = Expression.Add(dleft, dright);
                else
                    resbinexp = Expression.Subtract(dleft, dright);
                return resbinexp;
            }
            else if (node.NodeType == ExpressionType.Multiply)
            {   //乘法 
                BinaryExpression binexp = (BinaryExpression)node;
                Expression left = binexp.Left;
                Expression right = binexp.Right;

                Expression dleft = GetDerivative(left);
                Expression dright = GetDerivative(right);

                return Expression.Add(Expression.Multiply(dleft, right),
                    Expression.Multiply(left, dright));
            }
            else if (node.NodeType == ExpressionType.Parameter)
            {   // x导数 1  
                return Expression.Constant(1.0);
            }
            else if (node.NodeType == ExpressionType.Constant)
            {   // 常数导数  0
                return Expression.Constant(0.0);
            }
            else if (node.NodeType == ExpressionType.Call)
            {
                MethodCallExpression callexp = (MethodCallExpression)node;
                Expression arg0 = callexp.Arguments[0];
                Expression darg0 = GetDerivative(arg0);
                if (callexp.Method.Name == "Exp")
                {
                    // 指数
                    return Expression.Multiply(
                           Expression.Call(null, callexp.Method, arg0), darg0);
                }
                else if (callexp.Method.Name == "Sin")
                {
                    // 正弦
                    MethodInfo miCos = typeof(Math).GetMethod("Cos",
                                       BindingFlags.Public | BindingFlags.Static);
                    return Expression.Multiply(
                           Expression.Call(null, miCos, arg0), darg0);
                }
                else if (callexp.Method.Name == "Cos")
                {
                    // 余弦
                    MethodInfo miSin = typeof(Math).GetMethod("Sin",
                                       BindingFlags.Public | BindingFlags.Static);
                    return Expression.Multiply(
                           Expression.Negate(Expression.Call(null, miSin, arg0)), darg0);
                }
            }

            throw new NotImplementedException();       
        }

        static Func<double, double> GetDerivative(Expression<Func<double, double>> func)
        {
            // 从Lambda表达式中获得函数体  
            Expression resBody = GetDerivative(func.Body);

            // 需要续用Lambda表达式的自变量  
            ParameterExpression parX = func.Parameters[0];

            Expression<Func<double, double>> resFunc
                = (Expression<Func<double, double>>)Expression.Lambda(resBody, parX);

            Console.WriteLine("diff function = {0}", resFunc);
            return resFunc.Compile();
        }

        static double GetDerivative(Expression<Func<double, double>> func, double x)
        {
            Func<double, double> diff = GetDerivative(func);
            return diff(x);
        }

        static void Main(string[] args)
        {
             
            double y = GetDerivative(x => x*x+3*x , 2.0);
            Console.WriteLine("f'(x) = {0}", y);
        }
    }
}
