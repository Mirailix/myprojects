using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Npgsql;

namespace WindowsFormsApp4
{
    public partial class Update : Form
    {
        private static string a, b, c,d;

        private void Update_Load(object sender, EventArgs e)
        {
            textBox1.Text = b;
            textBox2.Text = c;
            textBox3.Text = d;
        }

        public Update(Form1 f1)
        {
            InitializeComponent();
            a = Convert.ToString(f1.dataGridView1.SelectedRows[0].Cells[0].Value);
            b = Convert.ToString(f1.dataGridView1.SelectedRows[0].Cells[1].Value);
            c = Convert.ToString(f1.dataGridView1.SelectedRows[0].Cells[2].Value);
            d = Convert.ToString(f1.dataGridView1.SelectedRows[0].Cells[3].Value);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            NpgsqlConnection con = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1; Database=leha");
            con.Open();
            string sql1 = String.Format("update client set FIO='{0}', address='{1}', phone='{2}' where id={3}", textBox1.Text, textBox2.Text, textBox3.Text, a);
            NpgsqlCommand cmd = new NpgsqlCommand(sql1, con);
            cmd.ExecuteNonQuery();
        }
    }
}
