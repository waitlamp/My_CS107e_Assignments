---
released: true
permalink: /labs/projectlab1/
title: 'Lab 8: Project Team Meeting 1'
readings: |
  + Lab will be a project work session. Plan to attend lab at same time as your teammates.
---
{% comment %}
__To prep for lab:__
- [ ] Remind students to attend lab together with their team
{% endcomment %}

### Goals

The final two weeks of lab sessions will be used as working meetings for the project teams. Plan to attend lab at same time as your teammates. 

Use the first week's meeting to confirm your project plan and task schedule. What cool aspect of computer systems will you explore?  What neat hardware do you want to involve? How will you coordinate with your team to execute on your plan? 

By the end of the lab session, you want to

- Settle on project plan with your team
- Curate the hardware/materials required, identify where to source any needed components
- Establish practices for effective communication and coordination with your team
- Enumerate milestones to hit by next week's lab (aim to resolve unknowns/risks ASAP)
- Check-in with us to confirm your plans seem on track for a great result

Refer to the [project writeup](/project/) for more information on the project itself.

### Project repository and project mirror repository

You've been git-wrangling all quarter as part of your individual development process; the benefits of revision control become even more critical when coordinating work across multiple authors. 

This quick lab exercise is to get your team started on using git collaboratively. Each project has its own remote repository on GitHub; you should have received an email invitation to access it. This remote repository is the "drop point" where your team synchronizes the joint work. You also should have received an email invitation to access the project mirror repo, which contains a skeleton project structure (Makefile included!) that you can use a starting point for your project. 

The basic workflow goes like this. Each team member has a local copy of the repository on their laptop. Edit files in the local repository and commit changes. When your latest work has stabilized to a state that is ready to share, use `git push` to send your updates to the remote. Your teammate then uses `git pull` to fetch changes from the remote which are brought into their local repository. 

One (and only one) team member should pull in the starter code from the
project repo. After changing to `cs107e_home` and cloning your team's project repository, this team member should do the following:

```bash
$ git remote add starter-code git@github.com:cs107e/project-mirror.git
$ git pull --allow-unrelated-histories starter-code master
$ git push 
```

The remaining team members should now change to the `cs107e_home` directory and clone your team's project repository. 

Now, all team members should do the following.
+ In the local repository, edit the file `Proposal.md` file and add your name to the list of team members.  Save the file.
+ Commit your change and push to Github.
+ Have your teammates pull your change.

During the pull/push operations, git will attempt to automatically merge changes made by different authors. However, if both you and a teammate have made overlapping edits, git will halt and report a "merge conflict". Git dumps both sets of changes into the conflicted file and fences the sections with marker symbols (`>>>`, `<<<`, `===`). You must manually resolve the sections in conflict. To do this, open the conflicted file, look for the marker symbols, edit the contents to select one/other/both changes as you see fit and remove the symbols. Save the file and commit it to complete the merge.

### Check in with TA

Before the end of the lab period, be sure to confirm the following items with us:

* What is the gist of your project?

* What do you wish to accomplish with your project?

* Can each of you access the team repository?

* What is your plan for acquiring any additional materials you need in a timely fashion? 

* What are the milestones to achieve by next week?

