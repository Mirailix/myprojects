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
    public partial class otchet : Form
    {
        DataSet ds = new DataSet();
        DataTable dt = new DataTable();
        public otchet()
        {
            InitializeComponent();
        }

        private void otchet_Load(object sender, EventArgs e)
        {
            string sql = "SELECT FIO FROM client";
            NpgsqlConnection conn = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1;Database=leha");
            conn.Open();
            NpgsqlCommand cmd = new NpgsqlCommand(sql, conn);
            using (NpgsqlDataReader reader = cmd.ExecuteReader())
            {
                while (reader.Read())
                {
                    checkedListBox1.Items.Add(reader["FIO"].ToString());
                }
            }
            conn.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            NpgsqlConnection conn = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1;Database=leha");
            conn.Open();
            DataSet ds = new DataSet();
            if (checkedListBox1.CheckedItems.Count != 0)
            {
                for (int i = 0; i < checkedListBox1.CheckedItems.Count; i++)
                {
                    string sql = string.Format("SELECT id FROM client WHERE FIO = '{0}'", checkedListBox1.CheckedItems[i]);
                    NpgsqlCommand cmd = new NpgsqlCommand(sql, conn);
                    int cl_id = 0;
                    using (NpgsqlDataReader reader = cmd.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            cl_id = Convert.ToInt32(reader["id"]);
                        }
                    }

                    /*
                    sql = string.Format("SELECT sale_info.info_id, sale_info.sale_id, goods.product_name, sale_info.number, sale_info.price, sale_info.nds FROM sale_info JOIN goods ON sale_info.product_id = goods.product_id WHERE sale_info.sale_id IN (SELECT sale_id FROM sale WHERE data < '{0}' AND client_id = '{1}')", dateTimePicker1.Value, cl_id);
                    NpgsqlDataAdapter da = new NpgsqlDataAdapter(sql, conn);

                    DataTableMapping tMap = da.TableMappings.Add("sale_info", "Sale info");
                    tMap.ColumnMappings.Add("info_id", "id инфо");
                    tMap.ColumnMappings.Add("sale_id", "id продажи");
                    tMap.ColumnMappings.Add("product_name", "Название товара");
                    tMap.ColumnMappings.Add("number", "Количество");
                    tMap.ColumnMappings.Add("price", "Цена");
                    tMap.ColumnMappings.Add("nds", "НДС");

                    da.Fill(ds, "sale_info");

                    */

                    String sql1 = string.Format("select client.FIO, orders.id,tovars.name,details.kolvo-details.dostavleno as r, (details.kolvo-details.dostavleno)*details.price as razn from client join orders on client.id = orders.id_client join details on details.id_orders = orders.id join tovars on details.id_tovars = tovars.id where client.id={0}  ; ", cl_id);
                    NpgsqlDataAdapter da = new NpgsqlDataAdapter(sql1, conn);

                    da.Fill(ds,"client");
                }
                dataGridView1.DataSource = ds.Tables["client"].DefaultView;
            }

            conn.Close();
        }
    }
}
