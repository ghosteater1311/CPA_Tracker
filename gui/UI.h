#ifndef UI_H
#define UI_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QCloseEvent>
#include "Calculator.h"

// Define UI Class
class UI:
    public QMainWindow
    {
        // Object Macro
        Q_OBJECT
        private:
            // Attributes and Method in private
            bool isModified = false;
            QTableWidget *table;
            QLabel *resultLabel;
            Calculator calculator;
            QString currentFile;
            std::vector<Course> getCoursesFromTable() const;
            void updateTableFromVector(const std::vector<Course>& courses);
            bool showCourseDialog(QString &code, QString &name, int &credits, QString &grade, QString &gradeAlpha);

        protected:
            // Close event handling
            void closeEvent(QCloseEvent *event) override;
        
        public:
            // Constructor
            UI(QWidget *parent = nullptr);

        private slots:
            // Methods
            void onAddCourse();
            void onCalculate();
            void onRemoveCourse();
            void onEditCourse();
            void onOpenFile();
            void onSaveAs();
            void onSaveFile();
            void onCloseFile();
            void onSortAscending();
            void onSortDescending();
            void onSearchCode();
            void onSearchName();
    };

#endif