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
    public partial class Add_detail : Form
    {
        private static string a;
        public Add_detail(Orders f1)
        {
            InitializeComponent();
            a = Convert.ToString(f1.dataGridView1.SelectedRows[0].Cells[0].Value);
        }

        private void Add_detail_Load(object sender, EventArgs e)
        {
            NpgsqlConnection con = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1; Database=leha");
            DataSet ds = new DataSet();
            DataTable dt = new DataTable();
            NpgsqlDataAdapter da;
            //textBox1.Text = a;
            string sql = "Select * from tovars";
            da = new NpgsqlDataAdapter(sql, con);
            ds.Reset();
            da.Fill(ds);
            dt = ds.Tables[0];
            comboBox1.DataSource = dt;
            comboBox1.DisplayMember = "name";
            comboBox1.ValueMember = "id";
            comboBox1.SelectedIndex = -1;

        }

        private void button1_Click(object sender, EventArgs e)
        {
            NpgsqlConnection conn = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1; Database=leha");
            conn.Open();
            String sql = String.Format("insert into details (id_orders, id_tovars, kolvo, price, dostavleno) values ('{0}','{1}',{2},{3},'{4}')", a, comboBox1.SelectedValue.ToString(), textBox1.Text, textBox2.Text, textBox3.Text);
            NpgsqlCommand cmd = new NpgsqlCommand(sql, conn);
            cmd.ExecuteNonQuery();
            conn.Close();
            textBox1.Text = " ";
            textBox2.Text = " ";
            textBox3.Text = " ";
        }
    }
}
