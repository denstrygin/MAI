using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SharpGL;

namespace SharpGL
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        float rquad = 0;

        private void openGLControl1_OpenGLDraw(object sender, RenderEventArgs args)
        {
            // Создаем экземпляр
            OpenGL gl = this.openGLControl1.OpenGL;
            // Очистка экрана и буфера глубин
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);

            // Сбрасываем модельно-видовую матрицу 
            gl.LoadIdentity();
            // Сдвигаем перо вправо от центра и вглубь экрана
            gl.Translate(0.0f, 0.0f, -10.0f);
            // Вращаем вокруг диагональной линии
            gl.Rotate(rquad, 1.0f, 1.0f, 1.0f);
            // Рисуем треугольниками - грани додэкаедара
            gl.Begin(OpenGL.GL_TRIANGLES);

            // Первая грань
            gl.Color(0.0f, 1.0f, 0.0f);
            gl.Vertex(0.0f, -(0.5 + Math.Sqrt(5) / 2), 1 / (0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(0.0f, -(0.5 + Math.Sqrt(5) / 2), -1 / (0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(1.0f, -1.0f, 1.0f);

            gl.Vertex(0.0f, -(0.5 + Math.Sqrt(5) / 2), -1 / (0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(1.0f, -1.0f, -1.0f);
            gl.Vertex(1.0f, -1.0f, 1.0f);

            gl.Vertex(1.0f, -1.0f, -1.0f);
            gl.Vertex(1.0f, -1.0f, 1.0f);
            gl.Vertex(0.5 + Math.Sqrt(5) / 2, -1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);



            //Вторая грань
            gl.Color(1.0f, 0.0f, 0.0f);
            gl.Vertex(1.0f, -1.0f, 1.0f);
            gl.Vertex(1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, 0.5 + Math.Sqrt(5) / 2);
            gl.Vertex(-1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, 0.5 + Math.Sqrt(5) / 2);

            gl.Vertex(-1.0f, -1.0f, 1.0f);
            gl.Vertex(1.0f, -1.0f, 1.0f);
            gl.Vertex(-1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, 0.5 + Math.Sqrt(5) / 2);

            gl.Vertex(0.0f, -(0.5 + Math.Sqrt(5) / 2), 1 / (0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(-1.0f, -1.0f, 1.0f);
            gl.Vertex(1.0f, -1.0f, 1.0f);


            //Третья грань
            gl.Color(0.0f, 0.0f, 1.0f);
            gl.Vertex(1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, 0.5 + Math.Sqrt(5) / 2);
            gl.Vertex(1.0f, -1.0f, 1.0f);
            gl.Vertex(1.0f, 1.0f, 1.0f);

            gl.Vertex(1.0f, -1.0f, 1.0f);
            gl.Vertex(1.0f, 1.0f, 1.0f);
            gl.Vertex(0.5 + Math.Sqrt(5) / 2, -1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);

            gl.Vertex(1.0f, 1.0f, 1.0f);
            gl.Vertex(0.5 + Math.Sqrt(5) / 2, -1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);
            gl.Vertex(0.5 + Math.Sqrt(5) / 2, 1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);


            // Четвёртая грань
            gl.Color(1.0f, 1.0f, 0.0f);
            gl.Vertex(0.0f, -(0.5 + Math.Sqrt(5) / 2), 1 / (0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(0.0f, -(0.5 + Math.Sqrt(5) / 2), -1 / (0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(-1.0f, -1.0f, 1.0f);

            gl.Vertex(-1.0f, -1.0f, 1.0f);
            gl.Vertex(-1.0f, -1.0f, -1.0f);
            gl.Vertex(0.0f, -(0.5 + Math.Sqrt(5) / 2), -1 / (0.5 + Math.Sqrt(5) / 2));

            gl.Vertex(-1.0f, -1.0f, 1.0f);
            gl.Vertex(-1.0f, -1.0f, -1.0f);
            gl.Vertex(-(0.5 + Math.Sqrt(5) / 2), -1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);


            // Пятая грань
            gl.Color(1.0f, 0.0f, 1.0f);
            gl.Vertex(0.0f, -(0.5 + Math.Sqrt(5) / 2), -1 / (0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(-1.0f, -1.0f, -1.0f);
            gl.Vertex(1.0f, -1.0f, -1.0f);

            gl.Vertex(1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, -(0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(-1.0f, -1.0f, -1.0f);
            gl.Vertex(1.0f, -1.0f, -1.0f);

            gl.Vertex(-1.0f, -1.0f, -1.0f);
            gl.Vertex(1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, -(0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(-1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, -(0.5 + Math.Sqrt(5) / 2));


            // Шетсая грань
            gl.Color(0.0f, 1.0f, 1.0f);
            gl.Vertex(1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, -(0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(1.0f, -1.0f, -1.0f);
            gl.Vertex(1.0f, 1.0f, -1.0f);

            gl.Vertex(0.5 + Math.Sqrt(5) / 2, -1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);
            gl.Vertex(1.0f, -1.0f, -1.0f);
            gl.Vertex(1.0f, 1.0f, -1.0f);

            gl.Vertex(0.5 + Math.Sqrt(5) / 2, -1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);
            gl.Vertex(0.5 + Math.Sqrt(5) / 2, 1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);
            gl.Vertex(1.0f, 1.0f, -1.0f);


            // Седьмая грань
            gl.Color(1.0f, 0.5f, 1.0f);
            gl.Vertex(-(0.5 + Math.Sqrt(5) / 2), -1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);
            gl.Vertex(-(0.5 + Math.Sqrt(5) / 2), 1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);
            gl.Vertex(-1.0f, -1.0f, -1.0f);

            gl.Vertex(-(0.5 + Math.Sqrt(5) / 2), 1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);
            gl.Vertex(-1.0f, -1.0f, -1.0f);
            gl.Vertex(-1.0f, 1.0f, -1.0f);

            gl.Vertex(-1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, -(0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(-1.0f, 1.0f, -1.0f);
            gl.Vertex(-1.0f, -1.0f, -1.0f);


            // Восьмая грань
            gl.Color(0.5f, 1.0f, 1.0f);
            gl.Vertex(-(0.5 + Math.Sqrt(5) / 2), -1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);
            gl.Vertex(-(0.5 + Math.Sqrt(5) / 2), 1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);
            gl.Vertex(-1.0f, 1.0f, 1.0f);

            gl.Vertex(-(0.5 + Math.Sqrt(5) / 2), -1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);
            gl.Vertex(-1.0f, 1.0f, 1.0f);
            gl.Vertex(-1.0f, -1.0f, 1.0f);

            gl.Vertex(-1.0f, 1.0f, 1.0f);
            gl.Vertex(-1.0f, -1.0f, 1.0f);
            gl.Vertex(-1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, 0.5 + Math.Sqrt(5) / 2);


            // Девятая грань
            gl.Color(1.0f, 1.0f, 0.5f);
            gl.Vertex(1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, 0.5 + Math.Sqrt(5) / 2);
            gl.Vertex(-1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, 0.5 + Math.Sqrt(5) / 2);
            gl.Vertex(1.0f, 1.0f, 1.0f);

            gl.Vertex(-1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, 0.5 + Math.Sqrt(5) / 2);
            gl.Vertex(1.0f, 1.0f, 1.0f);
            gl.Vertex(-1.0f, 1.0f, 1.0f);

            gl.Vertex(1.0f, 1.0f, 1.0f);
            gl.Vertex(-1.0f, 1.0f, 1.0f);
            gl.Vertex(0.0f, 0.5 + Math.Sqrt(5) / 2, 1 / (0.5 + Math.Sqrt(5) / 2));

            // Десятая грань
            gl.Color(0.5f, 0.5f, 1.0f);
            gl.Vertex(0.0f, 0.5 + Math.Sqrt(5) / 2, 1 / (0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(0.0f, 0.5 + Math.Sqrt(5) / 2, -1 / (0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(1.0f, 1.0f, 1.0f);

            gl.Vertex(0.0f, 0.5 + Math.Sqrt(5) / 2, -1 / (0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(1.0f, 1.0f, 1.0f);
            gl.Vertex(1.0f, 1.0f, -1.0f);

            gl.Vertex(1.0f, 1.0f, 1.0f);
            gl.Vertex(1.0f, 1.0f, -1.0f);
            gl.Vertex(0.5 + Math.Sqrt(5) / 2, 1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);


            // Одиннадцатая грань
            gl.Color(0.5f, 1.0f, 0.5f);
            gl.Vertex(1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, -(0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(-1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, -(0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(1.0f, 1.0f, -1.0f);

            gl.Vertex(-1 / (0.5 + Math.Sqrt(5) / 2), 0.0f, -(0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(1.0f, 1.0f, -1.0f);
            gl.Vertex(-1.0f, 1.0f, -1.0f);

            gl.Vertex(1.0f, 1.0f, -1.0f);
            gl.Vertex(-1.0f, 1.0f, -1.0f);
            gl.Vertex(0.0f, 0.5 + Math.Sqrt(5) / 2, -1 / (0.5 + Math.Sqrt(5) / 2));


            // Двенадцатая грань
            gl.Color(1.0f, 0.5f, 0.5f);
            gl.Vertex(0.0f, 0.5 + Math.Sqrt(5) / 2, -1 / (0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(0.0f, 0.5 + Math.Sqrt(5) / 2, 1 / (0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(-1.0f, 1.0f, -1.0f);

            gl.Vertex(0.0f, 0.5 + Math.Sqrt(5) / 2, 1 / (0.5 + Math.Sqrt(5) / 2));
            gl.Vertex(-1.0f, 1.0f, -1.0f);
            gl.Vertex(-1.0f, 1.0f, 1.0f);

            gl.Vertex(-1.0f, 1.0f, -1.0f);
            gl.Vertex(-1.0f, 1.0f, 1.0f);
            gl.Vertex(-(0.5 + Math.Sqrt(5) / 2), 1 / (0.5 + Math.Sqrt(5) / 2), 0.0f);

            gl.End();
            // Контроль полной отрисовки следующего изображения
            gl.Flush();
            // Меняем угол поворота 
            rquad -= 3.0f;
        }
    }
}