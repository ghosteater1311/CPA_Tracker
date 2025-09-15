#include "UI.h"
#include <Search.h>
#include <Sort.h>
#include <Course.h>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QAction>
#include <QMenuBar>
#include <QSpinBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QStackedWidget>
#include <QCloseEvent>
#include <QInputDialog>

// Constructor
UI::UI(QWidget *parent) : QMainWindow(parent)
{
    // Define Table 
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    table = new QTableWidget(0, 5, this);
    table->setHorizontalHeaderLabels({"Code", "Course", "Credits", "Grade", "GradeAlphabet"});
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layout->addWidget(table);

    // Define button for each options
    QPushButton *calcButton = new QPushButton("Calculate CPA", this);
    resultLabel = new QLabel("CPA: 0.0", this);

    // Define Menu Bar
    // 1. File
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    QMenu *fileMenu = menuBar->addMenu("&File");
    QAction *openAction = new QAction("Open File", this);
    QAction *saveAction = new QAction("Save", this);
    QAction *saveAsAction = new QAction("Save As...", this);
    QAction *closeAction = new QAction("Close File", this);
    
    // 2. Edit
    QMenu *editMenu = menuBar->addMenu("&Edit");
    QAction *addAction = new QAction("Add Course", this);
    QAction *editAction = new QAction("Edit the exist Course", this);
    QAction *removeAction = new QAction("Remove Course", this);

    // 3. Sort
    QMenu *sortMenu = menuBar->addMenu("&Sort");
    QAction *sortAscending = new QAction("Sort Courses Code by Ascending");
    QAction *sortDescending = new QAction("Sort Courses Code by Descending");

    // 4. Search 
    QMenu *searchMenu = menuBar->addMenu("&Find");
    QAction *searchCode = new QAction("Search by Course Code");
    QAction *searchName = new QAction("Search by Course Name");

    // Format the button into UI
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(calcButton);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAction);
    editMenu->addAction(addAction);
    editMenu->addAction(removeAction);
    editMenu->addAction(editAction);
    sortMenu->addAction(sortAscending);
    sortMenu->addAction(sortDescending);
    searchMenu->addAction(searchCode);
    searchMenu->addAction(searchName);
    layout->addWidget(resultLabel);
    layout->addLayout(buttonLayout);

    // Connect Buttons with their logic
    connect(calcButton, &QPushButton::clicked, this, &UI::onCalculate);
    connect(openAction, &QAction::triggered, this, &UI::onOpenFile);
    connect(saveAction, &QAction::triggered, this, &UI::onSaveFile);
    connect(saveAsAction, &QAction::triggered, this, &UI::onSaveAs);
    connect(closeAction, &QAction::triggered, this, &UI::onCloseFile);
    connect(addAction, &QAction::triggered, this, &UI::onAddCourse);
    connect(removeAction, &QAction::triggered, this, &UI::onRemoveCourse);
    connect(editAction, &QAction::triggered, this, &UI::onEditCourse);
    connect(sortAscending, &QAction::triggered, this, &UI::onSortAscending);
    connect(sortDescending, &QAction::triggered, this, &UI::onSortDescending);
    connect(searchCode, &QAction::triggered, this, &UI::onSearchCode);
    connect(searchName, &QAction::triggered, this, &UI::onSearchName);

    setCentralWidget(central);
}

// Inpout Course Dialog for reuseability
bool UI::showCourseDialog(QString &code, QString &name, int &credits, QString &grade, QString &gradeAlpha) 
{
    QDialog dialog(this);
    dialog.setWindowTitle("Course Information");
    QVBoxLayout mainLayout(&dialog);
    QStackedWidget *stacked = new QStackedWidget(&dialog);

    // Phase 1
    QWidget *page1 = new QWidget(&dialog);
    QVBoxLayout *page1Layout = new QVBoxLayout(page1);
    QFormLayout *form1 = new QFormLayout();
    QLineEdit *codeEdit = new QLineEdit(code, page1);
    QLineEdit *nameEdit = new QLineEdit(name, page1);
    QSpinBox *creditsEdit = new QSpinBox(page1);
    creditsEdit->setRange(1, 4);
    creditsEdit->setValue(credits > 0 ? credits : 1);
    form1->addRow("Course Code *", codeEdit);
    form1->addRow("Course Name *", nameEdit);
    form1->addRow("Credits *", creditsEdit);
    page1Layout->addLayout(form1);

    QHBoxLayout *page1Buttons = new QHBoxLayout();
    QPushButton *nextButton = new QPushButton("Next", page1);
    QPushButton *cancelButton1 = new QPushButton("Cancel", page1);
    page1Buttons->addWidget(nextButton);
    page1Buttons->addWidget(cancelButton1);
    page1Layout->addLayout(page1Buttons);

    // Phase 2
    QWidget *page2 = new QWidget(&dialog);
    QVBoxLayout *page2Layout = new QVBoxLayout(page2);
    QFormLayout *form2 = new QFormLayout();
    QComboBox *gradeEdit = new QComboBox(page2);
    gradeEdit->addItems({"", "0", "1.0", "1.5", "2.0", "2.5", "3.0", "3.5", "4.0"});
    gradeEdit->setCurrentText(grade);
    QLabel *alphaLabel = new QLabel(gradeAlpha, page2);
    QComboBox *alphaCombo = new QComboBox(page2);
    alphaCombo->addItems({"A", "A+"});
    alphaCombo->setVisible(grade == "4.0");
    if(grade == "4.0") alphaCombo->setCurrentText(gradeAlpha);
    form2->addRow("Grade", gradeEdit);
    form2->addRow("Grade Alphabet", alphaLabel);
    form2->addRow("", alphaCombo);
    page2Layout->addLayout(form2);

    QHBoxLayout *page2Buttons = new QHBoxLayout();
    QPushButton *prevButton = new QPushButton("Previous", page2);
    QPushButton *okButton = new QPushButton("OK", page2);
    QPushButton *cancelButton2 = new QPushButton("Cancel", page2);
    page2Buttons->addWidget(prevButton);
    page2Buttons->addWidget(okButton);
    page2Buttons->addWidget(cancelButton2);
    page2Layout->addLayout(page2Buttons);

    stacked->addWidget(page1);
    stacked->addWidget(page2);
    mainLayout.addWidget(stacked);

    // Button logic
    QObject::connect(nextButton, &QPushButton::clicked, [&]() 
    {
        if(codeEdit->text().isEmpty() || nameEdit->text().isEmpty()) 
        {
            QMessageBox::warning(&dialog, "Invalid Input", "Course Code and Name are required.");
            return;
        }
        stacked->setCurrentIndex(1);
    });
    QObject::connect(prevButton, &QPushButton::clicked, [&]() { stacked->setCurrentIndex(0); });
    QObject::connect(cancelButton1, &QPushButton::clicked, &dialog, &QDialog::reject);
    QObject::connect(cancelButton2, &QPushButton::clicked, &dialog, &QDialog::reject);
    QObject::connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    // Grade logic
    QObject::connect(gradeEdit, &QComboBox::currentTextChanged, [&](const QString &val) 
    {
        if(val == "0") alphaLabel->setText("F"), alphaCombo->setVisible(false);
        else if(val == "1.0") alphaLabel->setText("D"), alphaCombo->setVisible(false);
        else if(val == "1.5") alphaLabel->setText("D+"), alphaCombo->setVisible(false);
        else if(val == "2.0") alphaLabel->setText("C"), alphaCombo->setVisible(false);
        else if(val == "2.5") alphaLabel->setText("C+"), alphaCombo->setVisible(false);
        else if(val == "3.0") alphaLabel->setText("B"), alphaCombo->setVisible(false);
        else if(val == "3.5") alphaLabel->setText("B+"), alphaCombo->setVisible(false);
        else if(val == "4.0") alphaLabel->clear(), alphaCombo->setVisible(true);
        else alphaLabel->clear(), alphaCombo->setVisible(false);
    });

    if(dialog.exec() == QDialog::Accepted) 
    {
        code = codeEdit->text();
        name = nameEdit->text();
        credits = creditsEdit->value();
        grade = gradeEdit->currentText();
        gradeAlpha = (grade == "4.0") ? alphaCombo->currentText() : alphaLabel->text();
        return true;
    }
    return false;
}

// getCoursesFromTable Method
std::vector<Course> UI::getCoursesFromTable() const
{
    // TODO: Convert QTableWidget → std::vector<Course>
    std::vector<Course> courses;

    for(int i = 0; i < table->rowCount(); ++i) 
    {
        QString code = table->item(i, 0)->text();
        QString name = table->item(i, 1)->text();
        int credits = table->item(i, 2)->text().toInt();

        QString gradeStr;
        double grade = 0.0;
        if(table->item(i, 3)) 
        {
            gradeStr = table->item(i, 3)->text();
            grade = gradeStr.toDouble();
        }

        QString gradeAlpha;
        if(table->item(i, 4)) gradeAlpha = table->item(i, 4)->text();

        courses.emplace_back(code.toStdString(), name.toStdString(), credits, grade, gradeAlpha.toStdString());
    }
    return courses;
}

// updateTableFromVector Method
void UI::updateTableFromVector(const std::vector<Course>& courses) 
{
    // TODO: Convert std::vector<Course> → QTableWidget
    table->setRowCount(0);

    for(const auto& c : courses) 
    {
        int row = table->rowCount();
        table->insertRow(row);

        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(c.getCode())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(c.getName())));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(c.getCredits())));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(c.getGradePoint())));
        table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(c.getGradeAlphabet())));
    }
}

// Calucate button
void UI::onCalculate() 
{
    // TODO: logic Calculate
    calculator.clearCourses();
    for(int i = 0; i < table->rowCount(); i++) 
    {
        std::string code = table->item(i, 0)->text().toStdString();
        std::string name = table->item(i, 1)->text().toStdString();
        int credits = table->item(i, 2)->text().toInt();
        double grade = table->item(i, 3)->text().toDouble();
        std::string gradeAlphabet = table->item(i, 4)->text().toStdString();
        calculator.addCourse(Course(code, name, credits, grade, gradeAlphabet));
    }
    double cpa = calculator.calculateCPA();
    resultLabel->setText(QString("CPA: %1").arg(cpa));
}

// Add Sort Ascending Action
void UI::onSortAscending()
{
    // TODO: call HeapSort function of Sort.h for Sorting Ascending
    isModified = true;
    std::vector<Course> courses = getCoursesFromTable();
    Sort::heapSortByCode(courses, true);
    updateTableFromVector(courses);
}

// Add Sort Descending Action
void UI::onSortDescending()
{
    // TODO: call HeapSort function of Sort.h for Sorting Descending
    isModified = true;
    std::vector<Course> courses = getCoursesFromTable();
    Sort::heapSortByCode(courses, false);
    updateTableFromVector(courses);
}

// Search by Code Action
void UI::onSearchCode()
{
    // TODO: Search the Course by Code (Using BinarySearch Algorithm)
    bool ok;
    QString inputCode = QInputDialog::getText(this, "Search by Code", "Enter Course Code:", QLineEdit::Normal, "", &ok);
    if(!ok || inputCode.isEmpty()) return;

    auto courses = getCoursesFromTable();
    Sort::heapSortByCode(courses, true);

    int index = Search::binarySearchByCode(courses, inputCode.toStdString());
    if(index == -1) 
    {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Not Found",
            "Course not found!\nDo you want to Add Course?",
            QMessageBox::Yes | QMessageBox::No
        );
        if(reply == QMessageBox::Yes) 
        {
            onAddCourse();
        }
        return;
    }

    const Course &found = courses[index];
    QMessageBox::information(this, "Course Found",
        QString("Code: %1\nName: %2\nCredits: %3\nGrade: %4\nAlphabet: %5")
            .arg(QString::fromStdString(found.getCode()))
            .arg(QString::fromStdString(found.getName()))
            .arg(found.getCredits())
            .arg(found.getGradePoint())
            .arg(QString::fromStdString(found.getGradeAlphabet())));
}

// Search by Name Action
void UI::onSearchName()
{
    // TODO: Search the Course by Name (Using BinarySearch Algorithm)
    bool ok;
    QString inputName = QInputDialog::getText(this, "Search by Name",
                                              "Enter Course Name:", QLineEdit::Normal, "", &ok);
    if (!ok || inputName.isEmpty()) return;

    auto courses = getCoursesFromTable();
    Sort::introSortByName(courses, true);

    int index = Search::binarySearchByName(courses, inputName.toStdString());
    if(index == -1) 
    {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Not Found",
            "Course not found!\nDo you want to Add Course?",
            QMessageBox::Yes | QMessageBox::No
        );
        if(reply == QMessageBox::Yes) 
        {
            onAddCourse();
        }
        return;
    }

    const Course &found = courses[index];
    QMessageBox::information(this, "Course Found",
        QString("Code: %1\nName: %2\nCredits: %3\nGrade: %4\nAlphabet: %5")
            .arg(QString::fromStdString(found.getCode()))
            .arg(QString::fromStdString(found.getName()))
            .arg(found.getCredits())
            .arg(found.getGradePoint())
            .arg(QString::fromStdString(found.getGradeAlphabet())));
}

// Add course action
void UI::onAddCourse() 
{
    QString code, name, grade, gradeAlpha;
    int credits = 0;

    if(showCourseDialog(code, name, credits, grade, gradeAlpha)) 
    {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(code));
        table->setItem(row, 1, new QTableWidgetItem(name));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(credits)));
        table->setItem(row, 3, new QTableWidgetItem(grade));
        table->setItem(row, 4, new QTableWidgetItem(gradeAlpha));
        isModified = true;
    }
}

// Remove course action
void UI::onRemoveCourse()
{
    // TODO: logic to remove a course row to the table
    while(true) 
    {
        bool ok;
        QString key = QInputDialog::getText(this, "Remove Course", "Enter Course Code or Name:", QLineEdit::Normal, "", &ok);
        if(!ok || key.isEmpty()) return;

        int rowFound = -1;
        for(int i = 0; i < table->rowCount(); i++) 
        {
            QString code = table->item(i, 0) ? table->item(i, 0)->text() : "";
            QString name = table->item(i, 1) ? table->item(i, 1)->text() : "";
            if(code == key || name.compare(key, Qt::CaseInsensitive) == 0) 
            {
                rowFound = i;
                break;
            }
        }

        if(rowFound == -1) 
        {
            QMessageBox::warning(this, "Not Found", "Course not found! Try again.");
            continue;
        }

        QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Removal", "Do you want to remove this Course?", QMessageBox::Yes | QMessageBox::No);

        if(reply == QMessageBox::Yes) 
        {
            table->removeRow(rowFound);
            QMessageBox::information(this, "Removed", "Remove Successfully!");
            isModified = true;
            return;
        } 
        else 
        {
            continue; // back to input loop
        }
    }
}

// Edit course action
void UI::onEditCourse()
{
    // TODO: logic to edit the Course
    bool ok;
    QString code = QInputDialog::getText(this, "Edit Course", "Enter Course Code:", QLineEdit::Normal, "", &ok);
    if(!ok || code.isEmpty()) return;

    int rowFound = -1;
    for(int i = 0; i < table->rowCount(); i++) 
    {
        if(table->item(i,0) && table->item(i,0)->text() == code) 
        {
            rowFound = i; break;
        }
    }

    if(rowFound == -1) 
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Not Found",
            "Course not found! Do you want to Add Course?",
            QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes) onAddCourse();
        return;
    }

    QString name = table->item(rowFound,1)->text();
    int credits = table->item(rowFound,2)->text().toInt();
    QString grade = table->item(rowFound,3)->text();
    QString gradeAlpha = table->item(rowFound,4)->text();

    if(showCourseDialog(code, name, credits, grade, gradeAlpha)) 
    {
        table->setItem(rowFound, 0, new QTableWidgetItem(code));
        table->setItem(rowFound, 1, new QTableWidgetItem(name));
        table->setItem(rowFound, 2, new QTableWidgetItem(QString::number(credits)));
        table->setItem(rowFound, 3, new QTableWidgetItem(grade));
        table->setItem(rowFound, 4, new QTableWidgetItem(gradeAlpha));
        isModified = true;
    }
}

// Open action
void UI::onOpenFile() 
{
    // TODO: open file logic
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "CSV Files (*.csv)");
    if(fileName.isEmpty()) return;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) 
    {
        QMessageBox::warning(this, "Error", "Cannot open file!");
        return;
    }

    currentFile = fileName;
    QTextStream in(&file);
    table->setRowCount(0); // clear table 
    int row = 0;

    while(!in.atEnd()) 
    {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        table->insertRow(row);
        for(int col = 0; col < fields.size(); col++) 
        {
            table->setItem(row, col, new QTableWidgetItem(fields[col]));
        }
        row++;
    }
    file.close();

    table->setColumnWidth(0, 80);   // Code
    table->setColumnWidth(1, 350);  // Course
    table->setColumnWidth(2, 80);   // Credits
    table->setColumnWidth(3, 80);   // Grade
    table->setColumnWidth(4, 120);  // GradeAlphabet
    isModified = true;
}

// Save As action
void UI::onSaveAs() 
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "CSV Files (*.csv)");
    if(fileName.isEmpty()) return;

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) 
    {
        QMessageBox::warning(this, "Error", "Cannot save file!");
        return;
    }

    QTextStream out(&file);

    QStringList headers;
    for(int col = 0; col < table->columnCount(); col++) 
    {
        headers << table->horizontalHeaderItem(col)->text();
    }
    out << headers.join(",") << "\n";

    for(int row = 0; row < table->rowCount(); row++) 
    {
        QStringList fields;
        for(int col = 0; col < table->columnCount(); col++) 
        {
            QTableWidgetItem* item = table->item(row, col);
            fields << (item ? item->text() : "");
        }
        out << fields.join(",") << "\n";
    }

    file.close();
    currentFile = fileName;
    isModified = false;
    QMessageBox::information(this, "Save As", "File saved successfully!");
}

// Save action
void UI::onSaveFile()
{
    if(currentFile.isEmpty()) 
    {
        onSaveAs();
        return;
    }

    QFile file(currentFile);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) 
    {
        QMessageBox::critical(this, "Save Error", "Cannot open file for writing.");
        return;
    }

    QTextStream out(&file);

    QStringList headers;
    for(int col = 0; col < table->columnCount(); col++) 
    {
        headers << table->horizontalHeaderItem(col)->text();
    }
    out << headers.join(",") << "\n";

    for(int i = 0; i < table->rowCount(); i++) 
    {
        QStringList rowContent;
        for(int j = 0; j < table->columnCount(); j++) 
        {
            QTableWidgetItem* item = table->item(i, j);
            rowContent << (item ? item->text() : "");
        }
        out << rowContent.join(",") << "\n";
    }

    file.close();
    isModified = false;
    QMessageBox::information(this, "Save", "File saved successfully!");
}

// Close action
void UI::onCloseFile()
{
    if(table->rowCount() > 0 || isModified) 
    {
        if (isModified)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(
                this,
                "Close File",
                "Do you want to save changes before closing?",
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
            );

            if(reply == QMessageBox::Yes) 
            {
                onSaveFile();
            } 
            else if(reply == QMessageBox::Cancel) 
            {
                return;
            }
        }
    }

    table->setRowCount(0);
    currentFile.clear();
    isModified = false;
}

// Close Event Handling
void UI::closeEvent(QCloseEvent *event)
{
    // TODO: Logic to press close button on Window do
    int prevRowCount = table->rowCount();
    QString prevFile = currentFile;

    onCloseFile();

    // If user cancelled inside onCloseFile(), table->rowCount() and currentFile won't reset
    if(prevRowCount > 0 && table->rowCount() == prevRowCount && currentFile == prevFile) 
    {
        event->ignore(); // user pressed Cancel → block closing
    } 
    else 
    {
        event->accept(); // normal exit
    }
}