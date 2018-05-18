using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WatermarkApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private String imagePath;
        private String imagePathW;
        private readonly BackgroundWorker _worker = new BackgroundWorker();

        public MainWindow()
        {
            InitializeComponent();

            _worker.DoWork += _worker_DoWork;
            _worker.RunWorkerCompleted += _worker_RunWorkerCompleted;
        }

        #region thread functions

        private void _worker_RunWorkerCompleted(object sender,
                                               RunWorkerCompletedEventArgs e)
        {
            if (e.Error == null)
            {
                if (e.Result is BitmapSource)
                {
                    ResultImage.Source = null;
                    GC.Collect();
                    ResultImage.Source = e.Result as BitmapSource;
                    ResultZoomBorder.Reset();
                }
            }
            else
            {
                MessageBox.Show(e.Error.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
            ProgressIndicator.IsBusy = false;
        }


        private void _worker_DoWork(object sender, DoWorkEventArgs e)
        {
            using (var detector = new dv.EngineWrapper())
            {
                BitmapSource bmp = detector.Process(imagePath, imagePathW);
                bmp.Freeze();
                e.Result = bmp;
            }
            System.Threading.Thread.Sleep(1000);
        }

        #endregion

        #region Form Events

        private void buttonBrowseTemplate_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();

            // Set filter for file extension and default file extension 
            dlg.Multiselect = false;
            dlg.Filter = "All Graphics Types|*.bmp;*.jpg;*.jpeg;*.png;*.tif;*.tiff" +
       "BMP|*.bmp|GIF|*.gif|JPG|*.jpg;*.jpeg|PNG|*.png|TIFF|*.tif;*.tiff|";

            Nullable<bool> result = dlg.ShowDialog();

            if (result == true)
            {
                string filename = dlg.FileName;
                imagePath = filename;
                TextBoxImageName.Text = System.IO.Path.GetFullPath(filename).ToString();
                MasterImage.Source = new BitmapImage(new Uri(filename));
                MasterZoomBorder.Reset();
            }
        }



        private void buttonDetect_Click(object sender, RoutedEventArgs e)
        {
            ProgressIndicator.IsBusy = true;
            try
            {
                _worker.RunWorkerAsync();
            }
            catch (Exception ex)
            {
                ProgressIndicator.IsBusy = false;
                MessageBox.Show(ex.Message.ToString());
            }
        }
        #endregion

        private void ButtonBrowseTemplateW_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();

            // Set filter for file extension and default file extension 
            dlg.Multiselect = false;
            dlg.Filter = "All Graphics Types|*.bmp;*.jpg;*.jpeg;*.png;*.tif;*.tiff" +
       "BMP|*.bmp|GIF|*.gif|JPG|*.jpg;*.jpeg|PNG|*.png|TIFF|*.tif;*.tiff|";

            Nullable<bool> result = dlg.ShowDialog();

            if (result == true)
            {
                string filename = dlg.FileName;
                imagePathW = filename;
                TextBoxImageNameW.Text = System.IO.Path.GetFullPath(filename).ToString();
                MasterImageW.Source = new BitmapImage(new Uri(filename));
                MasterZoomBorderW.Reset();
            }
        }
    }
}
