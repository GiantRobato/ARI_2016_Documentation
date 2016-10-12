# ARI_2016_Documentation
Dedicated documentation for the 2016 UAA URC team.

Contents
========
- [Team](#Team)
- [Coding Tips & Tricks](#Tips-&-Tricks)

## Team
* Programming Team
	* Dustin Mendoza
	* Trevor Sprague

## Tips & Tricks

### Creating branchs

In order to create a branch, run the following in your shell (git shell / bash / etc.)

```bash
git checkout -b <branch name> 
git push origin <branch name>
```
To check if we successfuly created the branch you can run the following:

```bash
git branch
```

it should list something like the following:

```bash
	master
*	<branch name>
```