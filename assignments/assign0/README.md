---
released: true
permalink: /assignments/assign0/
title: "Assignment 0: Git oriented"
toc: true
duedate: 2021-09-28 11:59 PM
---

{% comment %}
Task list to copy/paste when creating PR for this assign:

**Before releasing assign0:**

- [ ] Review writeup/starter files/process (TA)
- [ ] Followup on issues from previous quarter postmortem (issue #221)

**To prep for assign0:**

- [ ]

{% endcomment %}

_Written by Omar Rizwan, updated by Peter McEvoy and Sean Konz for Winter 2021_

{% include duedate.html n=0 %}

<small>This assignment is not for a grade, but it's critical that you understand all the topics covered and that you complete it on-time so that you are ready to tackle the upcoming assignments. If you run into troubles, please reach out on Ed ASAP.</small>

## Goals

Your goal for this assignment is three-fold:

1. Get access to lab: Packard Basement 053
2. Walk through and understand the assignment workflow
3. Practice with your tools and refresh on background concepts


The tasks you will do include downloading the starter files, editing the files, committing your changes, and submitting for grading.

This is the same workflow you will use for each assignment in the course. Our process uses the
[git](<https://en.wikipedia.org/wiki/Git_(software)>) version control
system and the [GitHub](https://github.com) repository hosting service. Note
that this assignment assumes that you've completed [lab0](/labs/lab0) in its
entirety. If you haven't done so, please go back and ensure that you've
completed all of the steps.

## Steps

### 0. Gain access to Packard 053 

In order to gain access to the lab please complete EHS-4200 training on Axess Stars Trainings. 

https://ehs.stanford.edu/training/ehs-4200-general-safety

Once that is done email a completion confirmation or screenshot to Kenneth Green: 

Kenneth J Green: 

<kennygee@stanford.edu>

In your email include the following information: 
1)Your name 
2) SUID# 
3) that you are a CS107E student and need 24-hour acess to Packard and B053.  

### 1. Switch to the dev branch

Navigate to your local assignments repo and check which branch you're on:

```
$ cd ~/cs107e_home/assignments
$ git branch
```

If you're on `dev`, you're all set. Otherwise, switch to `dev`:

```
$ git checkout dev
```

### 2. Record your lab preference

Create a file named `lab.txt` and edit its contents so that it displays the following information:

```
<lab day> <intended lab arrival time>-<intended lab departure time>
```

i.e.

```
Wednesday 11:00am-1:00pm
```

You should expect to be at lab for at least 2 hours every week. Lab times are as follows: Wednesday 11am-1pm, 1pm-3pm, and 3pm-5pm. You should have received your lab assignment already. 

Save the file.

### 3. Commit your change locally and push it to remote

Now you are going to tell Git about the changes you have made. The commands below add the changed file to the staging index, commit staged changes (save to local repo), and push the commit to GitHub (update remote repo):

```
$ git status
$ git add lab.txt
$ git commit -m "Add lab time"
$ git push
```

You can use `git log` to view the history of commits in your local repo. When
you enter the log, you can exit out by pressing "q" on your keyboard. Also
verify that your changed `lab.txt` file shows up in your remote repo on GitHub.

```
$ git log
```

Also note that you can add multiple files (also called staging) and commit their
changes as a single commit. This is important because you don't ever want your code
to be in an inconsistent or bad state. For example, if you add a new file that
another file references, you want to put those two changes together in a single
commit; the file shouldn't be there if it isn't referenced, and you don't want
code to reference a file that doesn't exist.

Each commit that you make records a snapshot of your work. You can use these
snapshots to review your progress, compare versions, or identify and undo an
unfortunate change. Establishing good commit practices gives you the ability to
navigate the history of code changes, as well as providing the opportunity to
revert to previous versions. Sometimes you may find that you want to revert to
a commit before a set a changes that introduced a bug in your code. The more you
commit, the more opportunities you will have to restore previous working states
without losing as much work. **We recommend that you commit early and often and
that you write detailed commit messages.**

> Git command responses can sometimes look cryptic and scary. DON'T BE SCARED!!!
> Git is your friend :). Reading all the responses from git messages will help
> you understand the commands your running, and prevent you from missing
> important messages about the state of your repo.
> {: .callout-info}

**Note:** GitHub will show commits for `Branch: master` by default. To see the code and
changes for a specific assignment branch, switch to the branch by selecting it from `Branch` drop-down menu :

<img title="Changing to another branch." src="images/03-change-branch.png" width="400">

### 4. Answer background questions

Create a file called `background.txt` that contains answers to the following
questions. Please ensure that your responses are clearly labeled (i.e. we know
what question it corresponds to) and reasonably organized.

> **Tip** If you're stuck on any of the questions, take a look at the guides section
> of the course website, post on Ed, or start reading some articles online!
> {: .callout-info}

1. What is the result of performing a bitwise OR of the following two
   hexadecimal numbers (include the result in decimal): `0x0f OR 0xff`. Now left
   shift that number by 24; what is the result in hexadecimal? Assume numbers are 32-bit.

2. How many milliamperes of current will flow through a 1.5K resistor connected
   to 3V on one end and 0V (Ground) on the other end?

3. Find a file in the directory `/etc` on your computer; tell us the name of the
   file and the number of bytes contained in that file. How many files and
   directories are contained in the first level of directory `/etc`? Include
   the commands you used to answer these questions.

4. Change directory to your `cs107e.github.io` repo and find the folder named `cs107e`. What is the
   the absolute path to this folder? What is the relative path using the
   CS107E environment variable you created during your environment setup? Remember
   this folder location! Inside the `cs107e` there is an `include` folder where all your
   assignment header files are located. If you're having trouble with this, look up the command
   `pwd` and read [this] (https://cs107e.github.io/guides/unix/)

5. What editor do you plan on using? What is your plan on learning
   how to best use your editor? (i.e. for people using vim, you can run the
   vimtutor command from your terminal). Tell us a bit about how you customized your
   editor!

6. In git speak, what is a "commit"? What is a "branch"?
   If you're unsure, refer to our [git guide](/guides/git).

Use the `git` commands you learned in the previous steps to stage this file and
commit it to your local repository. Then, push your changes to GitHub.

<a name="submit"></a>
### 5. Tag submission commit
In future assignments, we'll run tests on your submission to verify that it works as
expected. You identify which commit that we test by using a tag. We'll
also use this tag to determine your submission time. In Git, a tag is simply a way
of giving a name to a particular commit. Create a tag to identify this assignment's
submission by doing the following:

```
$ git tag assign0-submission
$ git push --tags
```

Be sure you always name your submission flag with the format `assignX-submission`
where X is the particular assignment number. Now, go to your repo on GitHub and
verify that your newly created tag shows up in the "Tags" section of the branches
dropdown menu.

If you commit additional changes after creating the tag, you can
move the tag to a later commit with the following command (note that you need to push `--force` when moving a tag that already exists)

```
$ git tag -f assign0-submission
$ git push --tags --force
```

### 6. Create a pull request (submission)

In this course, assignment submission is done using GitHub's _pull request_
feature. Pull requests provide a summary view of changes made to the code as
well as a section for comments where course instructors will be providing
feedback.

The pull request model is used by many modern software projects to promote good
practices when working in a distributed development environment. The typical
flow starts with a base branch (often called _master_) that reflects the master
copy of the code. Feature development or bug fixing occurs by creating a new
_branch_ where changes are made. Once you're confident that the code in your
branch is polished, tested, and working well, you can ask other people to merge
the commits in your branch into _master_ by making a _pull request_. You've
pushed commits to your branch, you're now asking other people to pull those
commits into master. Team members use the pull request to review the
proposed changes and provide comments. When a team member approves the pull request,
GitHub automatically merges the commits back into the base branch.

In this class, we use this same workflow that is so common in software development
to review and grade your code. You write each assignment on a branch. To submit an
assignment, you make a pull request to merge it with the base branch, signifying
your code is ready to be added to your slowly growing library of code you'll use
to build your shell. The grader reviews your code and gives comments and bug reports.

View the contents of your remote repository on the web at `https://github.com/cs107e/[YOUR-GITHUB-USERNAME]-assignments`.
Switch to the branch `dev` by selecting it from the "Branch" drop-down
menu.

Click the 'New pull request' button.

<img title="We're on the right branch, so let's make a new pull request." src="images/04-new-pull-request.png" width="300">

Now you will see text entry boxes for describing the pull request, followed by
a list of the commits that you have made and a line-by-line comparison (`diff`)
of the changed files.

Set the Title to "Submit assign0" and leave the description blank (for
future assignments you can include comments for your grader in the
description).
<img title="Ready to create the pull request." src="images/06-create-pull-request.png" width="500">

Click 'Create pull request', which will submit the pull request and take you to
a page to view it:

<img title="Pull request page." src="images/07-pull-request.png" width="500">

The pull request page will update to reflect any changes that are pushed after
the initial submission. This page will also be used by graders to provide feedback
on your submissions.

You make one pull request per assignment. If you need to update your submission
after your initial pull request, simply edit your files, commit, retag, and push to add
it to the pull request. There is no need to make another pull request.

## Afterward: Grader's code review

Graders will review code by including line-specific and general comments on the
pull request page:

<img title="Comments." src="images/08-comments.png" width="500">

Click the 'Files changed' tab to see your whole solution from top to bottom,
along with any inline comments that the grader has added.

<img title="Files changed." src="images/09-files-changed.png" width="500">

When finished with their review, the grader will submit it so that you can view
the feedback. Graders will also run automated tests on your assignments to test
functionality. The results of these tests will be released within your (yet
uncreated) `logs/assignX` directory. The logs directory will contain the test output when
run with your implementation, as well as the expected output when
run with the staff solution. Your follow-up to those issues is to investigate test failures to find and fix the underlying bug. We expect you to have fixed any high priority core bugs on all your assignments by the time you submit assignment 7. Our goal
with this process is to replicate the process you'd follow if you were a
software engineer in industry. You'll almost never write code and forget about
it! The iterative process of writing code, and fixing bugs is as fundamental to
software engineering as mitochondria are to a living cell!
