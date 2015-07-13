#ifndef PAGINGTABLEVIEW_H
#define PAGINGTABLEVIEW_H

#include "defistruct.h"
#include "curlupload.h"
#include "typeindexvalue.h"
#include <QWidget>
class QSqlQuery;
class QMenu;
class QLabel;
class QCheckBox;
class QLineEdit;
class QPushButton;
class QTableView;
class TableModel;
class TableView;
class ButtonDelegate;
class IconDelegate;
class ImageDelegate;
class CheckBoxDelegate;
class MoveDelegate;
class QHBoxLayout;
class PagingTableView : public QWidget
{
    Q_OBJECT
public:
    explicit PagingTableView(QWidget *parent = 0, bool alternate_background_color = false);
    ~PagingTableView();
    void paintEvent(QPaintEvent *);
private:
    void initWidget();
    void setTableWidget();
    void widgetLayout();
    void actionMenu();
    void setWidgetValue();
public:
    void initPagingQueryLimitArgu();

signals:
    void checkBoxIsAll(bool checked);
    void currentRow(const int &row);
    void play(const int &row, int isPlay);
    void moveUp(const int &row);
    void moveDown(const int &row);
    void replace(const int &row);
    void skipMusic(const int &row,int isSkip);
    void matchMusic(const int &row, int isMatch);
    void modify(const int &row);
    void dele(const int &row);
    void add(const int &row);    

public slots:
    void update_View();
    void palyVideo(const QString &path);
public:
    void setShowCheckBox();
    void initMediaDelegate(bool isBlack = true);
    void initActorDelegate(bool isBlack = true);
    void setQueryActorDelegate();
    void setQueryMediaDelegate();
    void setFmDelegate();
    void setFmAddMusicDelegate(const QString &add_dele);
    void setFmShowMusicDelegate();
    void setAdDelegate();
    void setMediaListDelegate();
    void setInfoDelegate(int rows);
    void setAddModifyDelegate(const QString &add_dele);
    void setActorOnlineDelegate();
    void setMediaOnlineDelegate();
    void showUploadData(QSqlQuery &query, bool showMediaOrActor); ///true歌曲 false歌星
    void showUploadSingerAddModityData(QSqlQuery &query, QList< QString > &paths);
    void showUploadMediaListData(QSqlQuery &query);
    void setMediaValue(const QSqlQuery &query, QStringList &rowValue, int );
    void setActorValue(const QSqlQuery &query, const QString &runPath,
                       int , QStringList &rowValue);
    void setWidgetBottomHidden(const bool &hidden = true);

    void setModelValue(QList<QStringList> &data);
    void getValue(QList< QStringList > &rows);
private slots:

signals:
    void updateView(const PagingQueryLimitArgu &limit);
public slots:
    void up_page();
    void next_page();
    void first_page();
    void last_page();
    void jump_page(const int page);
    void show_page();

    void rowPageEditFinish();
    void jumpEditFinish();


public:    
    int setValidRowsCount(); ///获取有效行数
    void setTotal_Rows_Pages(const int rowsSize);

public:
    int total_page; //总页码
    int current_page; //当前页码
    int total_Rows;  //总共行数
    int row_page; //一页行数

    PagingQueryLimitArgu limitArgu;
    TableModel *model;
    QWidget *widget_bottom;
    TableView *tableView;
    QLabel *label_totalNum;
    QLabel *label_showPage;
    QLabel *label_toopTipLeft;
    QLabel *label_toopTipRight;

    QLineEdit *lineEdit_jump;
    QLineEdit *lineEdit_row;

    QPushButton *pushButton_upPage;
    QPushButton *pushButton_nextPage;
    QPushButton *pushButton_firstPage;
    QPushButton *pushButton_lastpage;
    QPushButton *pushButton_jumpPage;

    TypeIndexValue value;
    bool showMediaOrActor;   //true 歌曲  false 歌星
    bool alternate_background_color;
    bool isCheckBox;    
    QList< QStringList > rowList;
    CurlUpload *curlDownlaod;
    QString runPath;

    ButtonDelegate *m_cancelDelegate;
    IconDelegate *m_playDelegate;
    ImageDelegate *m_imageDelegate;
    CheckBoxDelegate * m_checkBoxDelegate;
    MoveDelegate *m_moveDelegate;
};

#endif // PAGINGTABLEVIEW_H
