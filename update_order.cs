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
    public partial class update_order : Form
    {
        private static string a, b, c,d;

        private void button1_Click(object sender, EventArgs e)
        {
            NpgsqlConnection con = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1; Database=leha");
            con.Open();
            string sql1 = String.Format("update orders set total_sum={0},id_client={1},date='{2}' where id={3}", textBox1.Text, comboBox1.SelectedValue.ToString(),textBox2.Text, a);
            NpgsqlCommand cmd = new NpgsqlCommand(sql1, con);
            cmd.ExecuteNonQuery();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        public update_order(Orders f1)
        {
            InitializeComponent();
            a = Convert.ToString(f1.dataGridView1.SelectedRows[0].Cells[0].Value);
            b = Convert.ToString(f1.dataGridView1.SelectedRows[0].Cells[1].Value);
            c = Convert.ToString(f1.dataGridView1.SelectedRows[0].Cells[2].Value);
            d = Convert.ToString(f1.dataGridView1.SelectedRows[0].Cells[3].Value);
        }

        private void update_detail_Load(object sender, EventArgs e)
        {
            NpgsqlConnection con = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1; Database=leha");
            DataSet ds = new DataSet();
            DataTable dt = new DataTable();
            NpgsqlDataAdapter da;
            string sql = "Select * from client";
            da = new NpgsqlDataAdapter(sql, con);
            ds.Reset();
            da.Fill(ds);
            dt = ds.Tables[0];
            comboBox1.DataSource = dt;
            comboBox1.DisplayMember = "name";
            comboBox1.ValueMember = "id";
            //comboBox1.SelectedIndex = int.Parse(c);
            textBox1.Text = b;
            textBox2.Text = d;
        }
    }
}
